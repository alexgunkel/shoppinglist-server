#include <gtest/gtest.h>

#include "serde/json_decorator.h"

TEST(EntryJsonDecoratorTest, testDerivation) {
    Entry orig{"foo", 2};
    EntryJsonDecorator decorator{orig};

    EXPECT_EQ("foo", decorator.getTitle());
    EXPECT_EQ(2, decorator.getAmount());
}

TEST(EntryJsonDecoratorTest, testToJson) {
    Entry orig{"Foo", 2};
    EntryJsonDecorator decorator{orig};

    auto result = decorator.toJson();
    EXPECT_EQ(web::json::value::string("Foo"), result["title"]);
    EXPECT_EQ(web::json::value::string("foo"), result["identifier"]);
    EXPECT_EQ(web::json::value::number(2), result["amount"]);
}

TEST(ListJsonDecoratorTest, testToJson) {
    List list;
    list.add({"for", 2});
    list.add({"bar", 3});

    const ListJsonDecorator decorator{list};

    const auto result = decorator.toJson();

    EXPECT_EQ(2, result.size()) << result.serialize();
    EXPECT_TRUE(result.at(0).is_object()) << result.at(0).serialize();
    EXPECT_TRUE(result.at(1).is_object()) << result.at(1).serialize();
}

TEST(EntryJsonDecoratorTest, testFromJson) {
    auto input = web::json::value::object();
    input["title"] = web::json::value::string("foo");
    input["amount"] = web::json::value::number(2);

    const auto result = EntryJsonDecorator::fromJson(input);

    EXPECT_EQ("foo", result.getTitle()) << input.serialize();
    EXPECT_EQ(2, result.getAmount()) << input.serialize();
}

TEST(EntryJsonDecoratorTest, testInvalidData) {
    std::map<std::string, web::json::value> invalidInputs;

    auto noTitle = web::json::value::object();
    noTitle["amount"] = web::json::value::number(2);
    invalidInputs["noTitle"] = noTitle;

    auto noAmount = web::json::value::object();
    noAmount["title"] = web::json::value::string("foo");
    invalidInputs["noAmount"] = noAmount;

    auto empty = web::json::value::object();
    invalidInputs["empty"] = empty;

    auto wrongTitleFormat = web::json::value::object();
    wrongTitleFormat["title"] = web::json::value::boolean(true);
    wrongTitleFormat["amount"] = web::json::value::number(2);
    invalidInputs["wrongTitleFormat"] = wrongTitleFormat;

    auto wrongAmountFormat = web::json::value::object();
    wrongAmountFormat["title"] = web::json::value::boolean(true);
    wrongAmountFormat["amount"] = web::json::value::number(2);
    invalidInputs["wrongAmountFormat"] = (wrongAmountFormat);

    for (const auto& [key, sample] : invalidInputs) {
        EXPECT_THROW(EntryJsonDecorator::fromJson(sample), InvalidJsonInput) << key << " didn't throw: " << sample.serialize();
    }
}
