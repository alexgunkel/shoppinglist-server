#ifndef LIST_REQUESTHANDLER_H
#define LIST_REQUESTHANDLER_H


#include <cpprest/http_msg.h>
#include "List.h"

struct Route {
    std::string entry;
    std::string list;

    static Route fromPath(const std::string& p);
};

class RequestHandler {
public:
    static void handlePut(const web::http::http_request&, List *);
    static void handleGet(const web::http::http_request&, List *);
    static void handlePost(const web::http::http_request&, List *);
    static void handleDelete(const web::http::http_request&, List *);
};


#endif //LIST_REQUESTHANDLER_H
