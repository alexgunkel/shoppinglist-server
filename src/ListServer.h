#ifndef LIST_LISTSERVER_H
#define LIST_LISTSERVER_H

#include <cpprest/http_listener.h>
#include "List.h"

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

class ListServer {
    web::http::experimental::listener::http_listener listener;

    List list;
public:
    explicit ListServer(const ListConfig& lConfig);
    void run();
};


#endif //LIST_LISTSERVER_H
