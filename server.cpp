#include <iostream>
#include <string>
#include "src/ListServer.h"
#include "src/config/config_reader.h"

int main(int argc, char *argv[]) {
    const ConfigReader configReader;
    const auto& config = configReader.getServerConfig();

    std::cout << "users in " << configReader.getServerConfig().getUserFile() << std::endl;
    auto auths = std::make_unique<AuthenticationRepository>(std::make_unique<HashingAlgorithm>());

    if (std::filesystem::exists(config.getUserFile())) {
        auths->readFile(config.getUserFile());
    }

    ListServer list{
            config,
            std::make_unique<RequestHandler>(
                    std::make_unique<AuthenticationCheck>(std::move(auths)),
                    std::make_shared<ListRepository>()
                    )
    };

    list.run();

    std::string line;
    getline(std::cin, line);

    return 0;
}
