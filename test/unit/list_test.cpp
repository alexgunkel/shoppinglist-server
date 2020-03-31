#include "list.h"

#include <gtest/gtest.h>

TEST(ListTest, testAddition) {
    List list;

    list.add({"milk", 1});
    list.add({"milk", 1});

    EXPECT_EQ(2, list.get("milk").getAmount());
}
