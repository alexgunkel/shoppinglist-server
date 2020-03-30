#include "ListServer.h"
#include "RequestHandler.h"

ListServer::ListServer(const ListConfig& lConfig) {
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

void ListServer::run() {
    std::cout << "listen on " << listener.uri().to_string() << std::endl;
    this->listener.open().wait();
}
