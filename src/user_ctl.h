#ifndef SHOPPING_LIST_USER_CTL_H
#define SHOPPING_LIST_USER_CTL_H

#include <memory>
#include <fstream>
#include "model/user.h"
#include "api/authentication_check.h"

class UserCtl {
    std::filesystem::path userFile;
    std::unique_ptr<HashingAlgorithm> hashing;
public:
    UserCtl(std::unique_ptr<HashingAlgorithm>, std::filesystem::path );

    [[nodiscard]] bool userExists(const User &) const;
    void addUser(const User &, const Password &) const;
    void setPassword(const User &, Password &) const;
    void removeUser(const User &);
};


#endif //SHOPPING_LIST_USER_CTL_H
