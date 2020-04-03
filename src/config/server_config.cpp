#include "server_config.h"

const std::filesystem::path &ServerConfig::getUserFile() const {
    return userFile;
}

void ServerConfig::setUserFile(const std::filesystem::path &file) {
    userFile = file;
}

const ServerName &ServerConfig::getServer() const {
    return server;
}

const Port &ServerConfig::getPort() const {
    return port;
}

ProtocolScheme ServerConfig::getScheme() const {
    return protocolScheme;
}

std::string ServerConfig::getAddress() const {
    return std::string(protocolScheme == ProtocolScheme::http ? "http" : "https") + "://" + server.get() + ":" + std::to_string(port.get());
}
