#include "json_decorator.h"

EntryJsonDecorator::EntryJsonDecorator(const Entry &orig): Entry{orig} {

}

web::json::value EntryJsonDecorator::toJson() const {
    auto result = web::json::value::object();
    result["title"] = web::json::value::string(getTitle());
    result["identifier"] = web::json::value::string(getIdentifier());
    result["amount"] = web::json::value::number(getAmount());

    return result;
}

EntryJsonDecorator EntryJsonDecorator::fromJson(const web::json::value &in) {
    if (!in.has_string_field("title") || !in.has_number_field("amount")) {
        throw InvalidJsonInput("missing field 'title'");
    }

    const auto title = in.at("title");
    const auto amount = in.at("amount");

    return EntryJsonDecorator{Entry{title.as_string(), amount.as_integer()}};
}

web::json::value ListJsonDecorator::toJson() const {
    auto list = web::json::value::array(size());

    int i = 0;
    for (const auto& [key, value] : get()) {
        list.at(i++) = EntryJsonDecorator{value}.toJson();
    }

    return list;
}

ListJsonDecorator::ListJsonDecorator(const List &list): List{list} {

}
