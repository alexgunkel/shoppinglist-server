#ifndef LIST_REQUEST_HANDLER_H
#define LIST_REQUEST_HANDLER_H

#include <cpprest/http_msg.h>
#include "list.h"
#include "json_decorator.h"

struct Route {
    std::string list;
    std::optional<std::string> entry;

    static Route fromPath(const std::string& p);
};

class RequestHandler {
public:
    static void handlePut(const web::http::http_request&, List *);
    static void handleGet(const web::http::http_request&, List *);
    static void handlePost(const web::http::http_request&, List *);
    static void handleDelete(const web::http::http_request&, List *);

    static EntryJsonDecorator extractEntry(const web::http::http_request &request);
};


#endif //LIST_REQUEST_HANDLER_H
