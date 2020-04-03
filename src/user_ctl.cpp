#include <fstream>
#include <utility>
#include "user_ctl.h"

bool UserCtl::userExists(const User &u) const {
    std::ifstream i{userFile};
    std::string line;
    size_t pos;

    while (std::getline(i, line)) {
        pos = line.find(':');

        if (pos != std::string::npos && u.get() == line.substr(0, pos)) {
            return true;
        }
    }

    return false;
}

UserCtl::UserCtl(std::unique_ptr<HashingAlgorithm> algorithm, std::filesystem::path  file): userFile{std::move(file)}, hashing{std::move(algorithm)} {

}

void UserCtl::addUser(const User &u, const Password &p) const {
    std::ofstream o{userFile, std::ios::app};
    o << u << ':' << hashing->hashPassword(p) << std::endl;
}
