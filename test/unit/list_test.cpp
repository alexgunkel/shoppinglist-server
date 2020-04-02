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

TEST(ListRepositoryTest, testAddAndGet) {
    ListRepository listRepository;

    listRepository.init(User{"foo"});
    EXPECT_TRUE(listRepository.has(User{"foo"}));
    EXPECT_FALSE(listRepository.has(User{"bar"}));
    EXPECT_ANY_THROW(auto x = listRepository.find(User{"bar"}));
    ASSERT_NE(nullptr, listRepository.find(User{"foo"}));
    listRepository.find(User{"foo"})->add(Entry{"Water", 1});
    EXPECT_EQ(1, listRepository.find(User{"foo"})->size());

    const auto moved = std::move(listRepository);
    ASSERT_NE(nullptr, moved.find(User{"foo"}));
    moved.find(User{"foo"})->add(Entry{"Bread", 1});
    EXPECT_EQ(2, moved.find(User{"foo"})->size());
}
