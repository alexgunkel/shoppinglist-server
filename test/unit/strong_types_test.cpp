#include "strong_types.h"

#include <gtest/gtest.h>

TEST(StrongTypesTest, testStrings) {
    Type<std::string, struct TypeA> foo{"foo"};
    Type<std::string, struct TypeA> bar{"bar"};

    EXPECT_EQ("foo", foo.get());
    EXPECT_FALSE(foo == bar);
    EXPECT_EQ((Type<std::string, struct TypeA>{"foobar"}), foo + bar);
}

TEST(StrongTypesTest, testInteger) {
    Type<int, struct TypeA> foo{10};
    Type<int, struct TypeA> bar{2};

    EXPECT_EQ(10, foo.get());
    EXPECT_TRUE(foo != bar);
    EXPECT_EQ((Type<int, struct TypeA>{12}), foo + bar);
}
