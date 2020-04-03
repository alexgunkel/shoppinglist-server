#include <iostream>
#include <string>
#include "src/ListServer.h"
#include "src/config/server_config.h"

int main(int argc, char *argv[]) {
    auto port = argv[1];
    auto auths = std::make_unique<AuthenticationRepository>(std::make_unique<HashingAlgorithm>());
    auths->addUser(User{"foo"}, Password{"bar"});
    ListServer list{
            {ServerName{"localhost"}, Port{atoi(port)}},
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
