#include <zconf.h>
#include <iostream>
#include "src/config/config_reader.h"
#include "src/model/user.h"
#include "src/api/authentication_check.h"
#include "src/user_ctl.h"
#include "src/exceptions.h"
#include <strong_types.h>

STRONG_TYPE(Command, std::string);

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    try {
        const Command cmd{argv[1]};
        const auto userName = argv[2];
        const ConfigReader configReader;

        UserCtl userCtl{std::make_unique<HashingAlgorithm>(), configReader.getServerConfig().getUserFile()};
        const User user{userName};

        if (cmd == Command{"add"} && !userCtl.userExists(user)) {
            std::cout << "Password for " << user << ": ";
            const auto password = getpass("");
            Password pass{password};

            userCtl.addUser(user, pass);

            std::cout << "\n" << "OK\n";
        } else if (cmd == Command{"hash"}) {
            HashingAlgorithm hashingAlgorithm;

            std::cout << "Password for " << user << ": ";
            const auto password = getpass("");
            Password pass{password};

            std::cout << hashingAlgorithm.hashPassword(pass) << std::endl;
            std::cout << hashingAlgorithm.hashPassword(pass) << std::endl;
            std::cout << hashingAlgorithm.hashPassword(pass) << std::endl;
        }

        return 0;
    } catch (const BadConfiguration &badConfiguration) {
        std::cerr << "Error: " << badConfiguration.what() << std::endl;

        return 1;
    }

}
