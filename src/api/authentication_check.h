#ifndef LIST_AUTHENTICATION_CHECK_H
#define LIST_AUTHENTICATION_CHECK_H

#include "../model/user.h"
#include <filesystem>
#include <string>
#include <map>
#include <bits/unique_ptr.h>

class HashingAlgorithm {
public:
    virtual ~HashingAlgorithm() = default;
    [[nodiscard]] virtual PasswordHash hashPassword(const Password &) const;
    [[nodiscard]] virtual bool checkPassword(const Password&, const PasswordHash&) const;
};

class AuthenticationRepository {
    std::unique_ptr<HashingAlgorithm> hasher;
    std::map<User, PasswordHash> knownUsers;
public:
    explicit AuthenticationRepository(std::unique_ptr<HashingAlgorithm>);
    [[nodiscard]] bool checkUser(const User &, const Password &) const;
    void addUser(const User &, const PasswordHash &);
    void addUser(const User &, const Password &);
    void readFile(const std::filesystem::path&);
};

class AuthenticationCheckInterface {
public:
    virtual ~AuthenticationCheckInterface() = default;
    [[nodiscard]] virtual bool check(const Base64&) const = 0;
};

class AuthenticationCheck: public AuthenticationCheckInterface {
    std::unique_ptr<AuthenticationRepository> repo;
public:
    explicit AuthenticationCheck(std::unique_ptr<AuthenticationRepository>);
    AuthenticationCheck(const AuthenticationCheck&) = delete;
    AuthenticationCheck &operator=(const AuthenticationCheck&) = delete;

    [[nodiscard]] bool check(const Base64 &) const override;
};


#endif //LIST_AUTHENTICATION_CHECK_H
