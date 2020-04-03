#ifndef SHOPPING_LIST_CONFIG_READER_H
#define SHOPPING_LIST_CONFIG_READER_H

#include "server_config.h"
#include <filesystem>

class ConfigReader {
    ServerConfig serverConfig{ServerName{}, Port{}};
public:
    explicit ConfigReader(const std::filesystem::path &pathToConfigFile);

    [[nodiscard]] const ServerConfig &getServerConfig() const;
};


#endif //SHOPPING_LIST_CONFIG_READER_H
