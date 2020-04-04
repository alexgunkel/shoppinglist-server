#include "user_ctl.h"

#include <gtest/gtest.h>
#include <fstream>

TEST(UserCtlTest, testUserExists) {
    const auto tmpFile = std::tmpnam(nullptr);
    std::ofstream out{tmpFile};

    out << "bar:hashed\n";
    std::flush(out);

    UserCtl userCtl{std::make_unique<HashingAlgorithm>(), tmpFile};
    EXPECT_FALSE(userCtl.userExists(User{"foo"}));
    EXPECT_TRUE(userCtl.userExists(User{"bar"}));
}

TEST(UserCtlTest, testAddUser) {
    const auto tmpFile = std::tmpnam(nullptr);

    UserCtl userCtl{std::make_unique<HashingAlgorithm>(), tmpFile};
    userCtl.addUser(User{"foo"}, Password{"bar"});

    std::ifstream i{tmpFile};
    std::string got;
    std::getline(i, got);

    EXPECT_EQ("foo:F27AB877EE002BAD7353436334E41AE847BE8B6F31F30CCF678BC7F1A4B9AD72", got);
}
