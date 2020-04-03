#ifndef SHOPPING_LIST_SERVER_CONFIG_H
#define SHOPPING_LIST_SERVER_CONFIG_H

#include <string>
#include <strong_types.h>

STRONG_TYPE(Port, int);
STRONG_TYPE(ServerName, std::string);

enum class ProtocolScheme {
    http,
    https,
};

class ServerConfig {
private:
    ServerName server;
    Port port;
    ProtocolScheme protocolScheme;

public:
    ServerConfig(const ServerName& serverName, Port port, ProtocolScheme scheme = ProtocolScheme::http)
    : server{serverName}
    , port{port}
    , protocolScheme{scheme}
    {};

    [[nodiscard]] const ServerName &getServer() const {
        return server;
    }

    [[nodiscard]] const Port &getPort() const {
        return port;
    }

    [[nodiscard]] std::string getScheme() const {
        return protocolScheme == ProtocolScheme::http ? "http" : "https";
    }

    [[nodiscard]] std::string getAddress() const {
        return getScheme() + "://" + server.get() + ":" + std::to_string(port.get());
    }
};


#endif //SHOPPING_LIST_SERVER_CONFIG_H
