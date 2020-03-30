#include "List.h"
#include <utility>
#include "App.h"

List::List(ListConfig config): config{std::move(config)} {
    uWS::App()
    .get("/ping", [](uWS::HttpResponse<false> *res, uWS::HttpRequest *req) {
        std::cout << req->getQuery() << std::endl;
        res->writeHeader("Content-Type", "text")->end("pong");
    })
    .put("/list", [this](uWS::HttpResponse<false> *res, uWS::HttpRequest *req) {
        std::cout << req->getParameter(1);

        res->end(req->getParameter(0));
    })
    .get("/list", [this](uWS::HttpResponse<false> *res, uWS::HttpRequest *req) {
        res->end("aqwsa");
    })
    .listen(config.getPort(), [&config](auto *token) {
        if (token) {
            std::cout << "listening on "
                << config.getScheme() << "://"
                << config.getServer() << ":"
                << config.getPort() << std::endl;
        }
    }).run();
}

std::string List::Address() const {
    return config.getScheme() + "://" + config.getServer();
}

List::~List() = default;
