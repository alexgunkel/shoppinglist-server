#include "authentication_check.h"
#include "pbkdf_2.h"

#include <cpprest/asyncrt_utils.h>

PasswordHash HashingAlgorithm::hashPassword(const Password &password) const {
    return Pbkdf2{password, "salt"}.getHash();
}

bool HashingAlgorithm::checkPassword(const Password &password, const PasswordHash &passwordHash) const {
    return Pbkdf2{password, "salt"}.getHash() == passwordHash;
}

AuthenticationRepository::AuthenticationRepository(std::unique_ptr<HashingAlgorithm> h): hasher{std::move(h)} {

}

void AuthenticationRepository::addUser(const User &u, const Password &p) {
    addUser(u, hasher->hashPassword(p));
}

void AuthenticationRepository::addUser(const User &u, const PasswordHash &p) {
    knownUsers[u] = p;
}

bool AuthenticationRepository::checkUser(const User &u, const Password &p) const {
    if (knownUsers.find(u) == knownUsers.end()) {
        return false;
    }

    return hasher->checkPassword(p, knownUsers.at(u));
}

void AuthenticationRepository::readFile(const std::filesystem::path &fileName) {
    std::ifstream inputs{fileName};
    std::string line;
    size_t colon;

    if (!inputs.is_open()) {
        throw std::runtime_error("file not readable: " + fileName.string());
    }

    while (getline(inputs, line)) {
        colon = line.find(':');
        knownUsers[User{line.substr(0, colon)}]
            = PasswordHash{line.substr(colon+1, line.size()-colon-1)};
    }
}

bool AuthenticationCheck::check(const Base64 &input) const {
    const auto decoded = utility::conversions::from_base64(input.get());
    const std::string credentials{decoded.begin(), decoded.end()};

    const auto colon = credentials.find(':');
    if (colon == std::string::npos) {
        throw std::runtime_error("invalid credentials: colon missing");
    }

    const auto user = User{credentials.substr(0, colon)};
    const auto password = Password{credentials.substr(colon+1, credentials.size()-colon-1)};
    return repo->checkUser(user, password);
}

AuthenticationCheck::AuthenticationCheck(std::unique_ptr<AuthenticationRepository> r): repo{std::move(r)} {

}
