#include "ListServer.h"
#include "api/request_handler.h"

ListServer::ListServer(const ServerConfig& lConfig, std::unique_ptr<RequestHandler> handler): requestHandler{std::move(handler)} {
    this->listener = web::http::experimental::listener::http_listener{lConfig.getAddress()};

    this->listener.support(
            web::http::methods::PUT,
            std::bind(&RequestHandler::handlePut, requestHandler.get(), std::placeholders::_1)
    );

    this->listener.support(
            web::http::methods::GET,
            std::bind(&RequestHandler::handleGet, requestHandler.get(), std::placeholders::_1)
            );

    this->listener.support(
            web::http::methods::POST,
            std::bind(&RequestHandler::handlePost, requestHandler.get(), std::placeholders::_1)
            );

    this->listener.support(
            web::http::methods::DEL,
            std::bind(&RequestHandler::handleDelete, requestHandler.get(), std::placeholders::_1)
            );
}

void ListServer::run() {
    std::cout << "listen on " << listener.uri().to_string() << std::endl;
    this->listener.open().wait();
}
