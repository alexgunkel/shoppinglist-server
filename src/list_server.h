#ifndef LIST_LIST_SERVER_H
#define LIST_LIST_SERVER_H

#include <cpprest/http_listener.h>
#include "list.h"

enum class ProtocolScheme {
    http,
    https,
};

class ListConfig {
private:
    std::string server;
    int port;
    ProtocolScheme protocolScheme;

public:
    ListConfig(std::string serverName, int port, ProtocolScheme scheme = ProtocolScheme::http)
            : server{std::move(serverName)}
            , port{port}
            , protocolScheme{scheme}
    {};

    [[nodiscard]] const std::string &getServer() const {
        return server;
    }

    [[nodiscard]] const int &getPort() const {
        return port;
    }

    [[nodiscard]] std::string getScheme() const {
        return protocolScheme == ProtocolScheme::http ? "http" : "https";
    }

    [[nodiscard]] std::string getAddress() const {
        return getScheme() + "://" + server + ":" + std::to_string(port);
    }
};

class list_server {
    web::http::experimental::listener::http_listener listener;

    List list;
public:
    explicit list_server(const ListConfig& lConfig);
    void run();
};


#endif //LIST_LIST_SERVER_H
