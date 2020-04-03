#ifndef LIST_LISTSERVER_H
#define LIST_LISTSERVER_H

#include <cpprest/http_listener.h>
#include "model/list.h"
#include "api/request_handler.h"
#include "config/server_config.h"

class ListServer {
    web::http::experimental::listener::http_listener listener;
    std::unique_ptr<RequestHandler> requestHandler;
public:
    explicit ListServer(const ServerConfig& lConfig, std::unique_ptr<RequestHandler>);
    void run();
};

#endif //LIST_LISTSERVER_H
