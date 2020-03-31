#include <iostream>
#include <string>
#include "src/list_server.h"

int main(int argc, char *argv[]) {
    auto port = argv[1];
    list_server list{
            {"localhost", atoi(port)}
    };

    list.run();


    std::string line;
    getline(std::cin, line);

    return 0;
}
