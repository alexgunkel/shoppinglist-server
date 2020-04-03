#ifndef LIST_JSON_DECORATOR_H
#define LIST_JSON_DECORATOR_H

#include <cpprest/json.h>
#include "../model/list.h"

class JsonDecorator {
public:
    [[nodiscard]] virtual web::json::value toJson() const = 0;
};

class EntryJsonDecorator: public Entry, JsonDecorator {
public:
    explicit EntryJsonDecorator(const Entry&);
    [[nodiscard]] web::json::value toJson() const override;

    static EntryJsonDecorator fromJson(const web::json::value&);
};

class InvalidJsonInput : public std::runtime_error {
public:
    explicit InvalidJsonInput(const std::string &msg): std::runtime_error{msg} {};
};

class ListJsonDecorator: public List, JsonDecorator {
public:
    explicit ListJsonDecorator(const List&);

    [[nodiscard]] web::json::value toJson() const override;
};

#endif //LIST_JSON_DECORATOR_H
