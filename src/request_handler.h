#ifndef LIST_REQUEST_HANDLER_H
#define LIST_REQUEST_HANDLER_H

#include <cpprest/http_msg.h>
#include "authentication_check.h"
#include "list.h"
#include "json_decorator.h"

struct Route {
    User user;
    std::optional<std::string> entry;

    static Route fromPath(const std::string& p);
};

class RequestHandler {
    std::unique_ptr<AuthenticationCheckInterface> authenticator;
    std::shared_ptr<ListRepository> listRepository;
public:
    explicit RequestHandler(std::unique_ptr<AuthenticationCheckInterface>, std::shared_ptr<ListRepository>);
    void handlePut(const web::http::http_request&);
    void handleGet(const web::http::http_request&);
    void handlePost(const web::http::http_request&);
    void handleDelete(const web::http::http_request&);

    static EntryJsonDecorator extractEntry(const web::http::http_request &request);
};


#endif //LIST_REQUEST_HANDLER_H
