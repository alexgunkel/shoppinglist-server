#include "RequestHandler.h"

void RequestHandler::handlePost(const web::http::http_request &request, List *list) {
    auto body = request.extract_json().get();
    auto amount = body["amount"];
    auto title = body["title"];

    list->add({title.as_string(), amount.as_integer()});
    auto result = list->get(title.as_string());

    auto obj = web::json::value::object();
    obj["amount"] = web::json::value::number(result.getAmount());
    obj["title"] = title;
    request.reply(web::http::status_codes::OK, obj);
}

void RequestHandler::handleGet(const web::http::http_request &request, List *list) {
    const auto route = Route::fromPath(request.request_uri().path());

    auto res = web::json::value::object();

    const auto& found = list->get(route.entry);

    res["title"] = web::json::value::string(found.getTitle());
    res["amount"] = web::json::value::number(found.getAmount());

    request.reply(web::http::status_codes::NotImplemented, res);
}

void RequestHandler::handlePut(const web::http::http_request &request, List *list) {
    request.reply(web::http::status_codes::NotImplemented);
}

void RequestHandler::handleDelete(const web::http::http_request &request, List *list) {
    request.reply(web::http::status_codes::NotImplemented);
}

Route Route::fromPath(const std::string& p) {
    auto path = web::uri::decode(p);
    auto splitPath = web::uri::split_path(path);

    if (splitPath.size() < 2) {
        throw std::runtime_error{"path needs to compare a list and an entry, got " + p};
    }

    return {splitPath.at(1), splitPath.at(0)};
}
