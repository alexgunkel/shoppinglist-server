#include <iostream>
#include <string>
#include "src/ListServer.h"

int main(int argc, char *argv[]) {
    auto port = argv[1];
    ListServer list{
            {"localhost", atoi(port)}
    };

    list.run();


    std::string line;
    getline(std::cin, line);

    return 0;
}
