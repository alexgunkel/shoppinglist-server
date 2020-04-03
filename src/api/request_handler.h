#ifndef LIST_REQUEST_HANDLER_H
#define LIST_REQUEST_HANDLER_H

#include <cpprest/http_msg.h>
#include "authentication_check.h"
#include "../model/list.h"
#include "../serde/json_decorator.h"

STRONG_TYPE(HeaderField, std::string);

struct Route {
    User user;
    std::optional<std::string> entry;

    static Route fromPath(const std::string& p);
};

class RequestHandler {
    std::unique_ptr<AuthenticationCheckInterface> authenticator;
    std::shared_ptr<ListRepository> listRepository;
public:
    HeaderField authorizationField{"Authorization"};

    explicit RequestHandler(std::unique_ptr<AuthenticationCheckInterface>, std::shared_ptr<ListRepository>);
    void handlePut(const web::http::http_request&);
    void handleGet(const web::http::http_request&);
    void handlePost(const web::http::http_request&);
    void handleDelete(const web::http::http_request&);

    [[nodiscard]] bool isAuthorized(const web::http::http_request&) const;

    static EntryJsonDecorator extractEntry(const web::http::http_request &request);
};


#endif //LIST_REQUEST_HANDLER_H
