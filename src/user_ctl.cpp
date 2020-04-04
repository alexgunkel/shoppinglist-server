#include <fstream>
#include <utility>
#include "user_ctl.h"
#include "exceptions.h"

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

    if (! o.is_open()) {
        throw FileNotWritable{userFile};
    }

    // @todo: find out, why the first run always results in a wrong hash
    const auto first = hashing->hashPassword(p);
    const auto second = hashing->hashPassword(p);
    const auto third = hashing->hashPassword(p);

    if (first != second && second != third) {
        throw std::runtime_error{"could not create password-hash"};
    }

    o << u << ':' << second << std::endl;

    o.flush();
    o.close();
}
