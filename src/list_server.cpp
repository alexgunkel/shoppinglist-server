#include "list_server.h"
#include "request_handler.h"

list_server::list_server(const ListConfig& lConfig) {
    this->listener = web::http::experimental::listener::http_listener{lConfig.getAddress()};

    this->listener.support(
            web::http::methods::PUT,
            std::bind(&RequestHandler::handlePut, std::placeholders::_1, &this->list)
    );

    this->listener.support(
            web::http::methods::GET,
            std::bind(&RequestHandler::handleGet, std::placeholders::_1, &this->list)
            );

    this->listener.support(
            web::http::methods::POST,
            std::bind(&RequestHandler::handlePost, std::placeholders::_1, &this->list)
            );

    this->listener.support(
            web::http::methods::DEL,
            std::bind(&RequestHandler::handleDelete, std::placeholders::_1, &this->list)
            );
}

void list_server::run() {
    std::cout << "listen on " << listener.uri().to_string() << std::endl;
    this->listener.open().wait();
}
