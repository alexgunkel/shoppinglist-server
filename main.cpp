#include <iostream>
#include <string>
#include "src/ListServer.h"

int main(int argc, char *argv[]) {
    auto port = argv[1];
    ListServer list{
            {"localhost", atoi(port)},
            std::make_unique<RequestHandler>(
                    std::make_unique<AuthenticationCheck>(
                            std::make_unique<AuthenticationRepository>(std::make_unique<HashingAlgorithm>())
                            ),
                    std::make_shared<ListRepository>()
                    )
    };

    list.run();


    std::string line;
    getline(std::cin, line);

    return 0;
}
