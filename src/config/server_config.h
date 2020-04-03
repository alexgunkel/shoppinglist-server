#ifndef SHOPPING_LIST_SERVER_CONFIG_H
#define SHOPPING_LIST_SERVER_CONFIG_H

#include <filesystem>
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

    std::filesystem::path userFile{""};
public:
    ServerConfig(const ServerName& serverName, Port port, ProtocolScheme scheme = ProtocolScheme::http)
    : server{serverName}
    , port{port}
    , protocolScheme{scheme}
    {};

    [[nodiscard]] const std::filesystem::path &getUserFile() const;

    void setUserFile(const std::filesystem::path &userFile);

    [[nodiscard]] const ServerName &getServer() const;

    [[nodiscard]] const Port &getPort() const;

    [[nodiscard]] ProtocolScheme getScheme() const;

    [[nodiscard]] std::string getAddress() const;
};


#endif //SHOPPING_LIST_SERVER_CONFIG_H
