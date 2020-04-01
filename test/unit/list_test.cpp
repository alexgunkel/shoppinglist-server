#include "list.h"

#include <gtest/gtest.h>

TEST(ListTest, testAddition) {
    List list;

    list.add({"milk", 1});
    list.add({"milk", 1});

    EXPECT_EQ(2, list.get("milk").getAmount());
}

TEST(EntryTest, testIdentifier) {
    std::map<std::string, std::string> samples = {
            {"foo", "foo"},
            {"Foo", "foo"},
            {"Foo Bar", "foo-bar"},
            {"Foo&Bar", "foo-bar"},
    };

    for (const auto& [input, wanted] : samples) {
        Entry entry{input, 2};
        EXPECT_EQ(wanted, entry.getIdentifier());
    }
}
