#include "request_handler.h"
#include "json_decorator.h"

void RequestHandler::handlePost(const web::http::http_request &request, List *list) {
    try {
        if (!request.body().is_valid()) {
            request.reply(web::http::status_codes::BadRequest);
            return;
        }
        const auto body = request.extract_json().get();
        const auto input = EntryJsonDecorator::fromJson(body);

        list->add(input);
        const auto result = EntryJsonDecorator{list->get(input.getTitle())};

        request.reply(web::http::status_codes::Accepted, result.toJson());
        return;
    } catch (const InvalidJsonInput &invalidJsonInput) {
        request.reply(web::http::status_codes::BadRequest);
        return;
    }

    request.reply(web::http::status_codes::InternalError);
}

void RequestHandler::handleGet(const web::http::http_request &request, List *list) {
    try {
        const auto route = Route::fromPath(request.request_uri().path());

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

void RequestHandler::handlePut(const web::http::http_request &request, List *list) {
    request.reply(web::http::status_codes::NotImplemented);
}

void RequestHandler::handleDelete(const web::http::http_request &request, List *list) {
    request.reply(web::http::status_codes::NotImplemented);
}

Route Route::fromPath(const std::string& p) {
    const auto path = web::uri::decode(p);
    const auto splitPath = web::uri::split_path(path);

    if (splitPath.empty()) {
        throw std::runtime_error{"path needs to contain a list, got " + p};
    }

    return {splitPath.at(0), splitPath.size() > 1 ? splitPath.at(1): std::optional<std::string>()};
}
