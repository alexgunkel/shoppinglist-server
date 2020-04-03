
#include <iostream>
#include "src/config/config_reader.h"
#include "src/model/user.h"
#include "src/api/authentication_check.h"
#include "src/user_ctl.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        return 1;
    }

    const auto userName = argv[1];
    const ConfigReader configReader;

    UserCtl userCtl{std::make_unique<HashingAlgorithm>(), configReader.getServerConfig().getUserFile()};
    const User user{userName};

    if (!userCtl.userExists(user)) {
        std::cout << "Password" << std::endl;

        std::string password;
        std::getline(std::cin, password);

        userCtl.addUser(user, Password{password});
    }

    return 0;
}
