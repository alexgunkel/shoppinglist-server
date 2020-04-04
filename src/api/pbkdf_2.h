#ifndef SHOPPING_LIST_PBKDF_2_H
#define SHOPPING_LIST_PBKDF_2_H

#include "../model/user.h"
#include <string>

class Pbkdf2 {
    Password password;
    std::string _salt;
public:
    Pbkdf2(const Password &, std::string salt);
    ~Pbkdf2() = default;

    [[nodiscard]] PasswordHash getHash() const;
    [[nodiscard]] bool checkHash(const PasswordHash &) const;
};


#endif //SHOPPING_LIST_PBKDF_2_H
