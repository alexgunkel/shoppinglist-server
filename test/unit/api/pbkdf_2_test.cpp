#include "api/pbkdf_2.h"
#include <gtest/gtest.h>

TEST(Pbkdf2Test, testHashing) {
    Password password{"bar"};
    Password password2{"foo"};

    const auto hash1 = Pbkdf2{password, "salt"}.getHash();
    const auto hash2 = Pbkdf2{password2, "salt"}.getHash();

    EXPECT_NE(hash1, hash2);

    EXPECT_TRUE((Pbkdf2{password, "salt"}.checkHash(hash1)));
    EXPECT_TRUE((Pbkdf2{password2, "salt"}.checkHash(hash2)));

    EXPECT_FALSE((Pbkdf2{password, "salt"}.checkHash(hash2)));
    EXPECT_FALSE((Pbkdf2{password2, "salt"}.checkHash(hash1)));
}
