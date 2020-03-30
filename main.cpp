#include <iostream>
#include <string>
#include "src/List.h"

int main(int argc, char *argv[]) {
    auto port = argv[1];
    List list{
            {"localhost", atoi(port)}
    };

    std::cout << "listen on " << list.Address() << std::endl;


    std::string line;
    getline(std::cin, line);

    return 0;
}
