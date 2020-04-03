#include <fstream>
#include <map>
#include "config_reader.h"

#include "exception.h"

using namespace std::filesystem;

ConfigReader::ConfigReader(const path &pathToConfigFile) {
    if (!is_regular_file(pathToConfigFile)) {
        throw InvalidConfigFile{"not a regular file", pathToConfigFile};
    }

    std::string line;
    std::ifstream input{pathToConfigFile};
    std::map<std::string, std::string> parsed;
    size_t pos;
    while (std::getline(input, line)) {
        pos = line.find('=');
        parsed[line.substr(0, pos)] = line.substr(pos+1, line.size() - pos - 1);
    }

    serverConfig = ServerConfig{
        ServerName{parsed.at("servername")},
        Port{atoi(parsed.at("port").data())}
    };
}

const ServerConfig &ConfigReader::getServerConfig() const {
    return serverConfig;
}
