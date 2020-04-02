#include "request_handler.h"

#include <utility>
#include "json_decorator.h"

void RequestHandler::handlePost(const web::http::http_request &request) {
    try {
        if (!isAuthorized(request)) {
            request.reply(web::http::status_codes::Unauthorized);
            return;
        }

        const auto route = Route::fromPath(request.request_uri().path());
        const auto input = extractEntry(request);

        if (!listRepository->has(route.user)) {
            listRepository->init(route.user);
        }

        const auto list = listRepository->find(route.user);
        list->add(input);

        const auto result = EntryJsonDecorator{list->get(input.getIdentifier())};

        request.reply(web::http::status_codes::Accepted, result.toJson());
        return;
    } catch (const InvalidJsonInput &invalidJsonInput) {
        request.reply(web::http::status_codes::BadRequest);
        return;
    }

    request.reply(web::http::status_codes::InternalError);
}

void RequestHandler::handleGet(const web::http::http_request &request) {
    try {
        if (!isAuthorized(request)) {
            request.reply(web::http::status_codes::Unauthorized);
            return;
        }

        const auto route = Route::fromPath(request.request_uri().path());

        if (!listRepository->has(route.user)) {
            listRepository->init(route.user);
        }

        const auto list = listRepository->find(route.user);

        request.reply(
                web::http::status_codes::OK,
                route.entry.has_value() ? EntryJsonDecorator{list->get(route.entry.value())}.toJson() : ListJsonDecorator(*list).toJson()
                );
        return;
    } catch (EntryNotFound &entryNotFound) {
        request.reply(web::http::status_codes::NotFound);
        return;
    }

    request.reply(web::http::status_codes::InternalError);
}

void RequestHandler::handlePut(const web::http::http_request &request) {
    try {
        if (!isAuthorized(request)) {
            request.reply(web::http::status_codes::Unauthorized);
            return;
        }

        const auto route = Route::fromPath(request.request_uri().path());

        if (!listRepository->has(route.user)) {
            listRepository->init(route.user);
        }

        const auto list = listRepository->find(route.user);

        const auto input = extractEntry(request);

        if (!route.entry.has_value()) {
            request.reply(web::http::status_codes::BadRequest);
            return;
        }

        list->set(route.entry.value(), input);

        request.reply(web::http::status_codes::Accepted);
        return;
    } catch (InvalidJsonInput &invalidJsonInput) {
        request.reply(web::http::status_codes::BadRequest);
        return;
    }
}

void RequestHandler::handleDelete(const web::http::http_request &request) {
    try {
        if (!isAuthorized(request)) {
            request.reply(web::http::status_codes::Unauthorized);
            return;
        }

        const auto route = Route::fromPath(request.request_uri().path());
        if (!listRepository->has(route.user)) {
            listRepository->init(route.user);
        }

        const auto list = listRepository->find(route.user);

        if (!route.entry.has_value()) {
            request.reply(web::http::status_codes::BadRequest);
            return;
        }

        list->drop(route.entry.value());
        request.reply(web::http::status_codes::Accepted);
        return;
    } catch (EntryNotFound &entryNotFound) {
        request.reply(web::http::status_codes::NotFound);
        return;
    }
}

EntryJsonDecorator RequestHandler::extractEntry(const web::http::http_request &request) {
    if (!request.body().is_valid()) {
        throw InvalidJsonInput("empty body");
    }

    return EntryJsonDecorator::fromJson(request.extract_json().get());
}

RequestHandler::RequestHandler(
        std::unique_ptr<AuthenticationCheckInterface> a,
        std::shared_ptr<ListRepository> list
        )
    : authenticator{std::move(a)}
    , listRepository{std::move(list)}
{
    //
}

bool RequestHandler::isAuthorized(const web::http::http_request &request) const {
    const auto authHeader = request.headers().find(authorizationField.get());
    if (authHeader == request.headers().end()) {
        return false;
    }

    return this->authenticator->check(Base64{authHeader->second});
}

Route Route::fromPath(const std::string& p) {
    const auto path = web::uri::decode(p);
    const auto splitPath = web::uri::split_path(path);

    if (splitPath.empty()) {
        throw std::runtime_error{"path needs to contain a list, got " + p};
    }

    return {User{splitPath.at(0)}, splitPath.size() > 1 ? splitPath.at(1): std::optional<std::string>()};
}
