#ifndef LIST_AUTHENTICATION_CHECK_H
#define LIST_AUTHENTICATION_CHECK_H

#include "strong_types.h"
#include <string>

using User = Type<std::string, struct UserType>;
using Password = Type<std::string, struct PasswordType>;
using PasswordHash = Type<std::string, struct PasswordHashType>;
using Base64 = Type<std::string, struct Base64Type>;

class AuthenticationRepository {
public:
    bool checkUser(const User &, const Password &) const;
    bool addUser(const User &, const std::string $passwordHash);

    static PasswordHash hashPassword(const Password &);
};

class AuthenticationCheck {
public:
    explicit AuthenticationCheck(const Base64 &);

    bool isValid() const;
};


#endif //LIST_AUTHENTICATION_CHECK_H
