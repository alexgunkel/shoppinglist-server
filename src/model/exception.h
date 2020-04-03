#ifndef SHOPPING_LIST_EXCEPTION_H
#define SHOPPING_LIST_EXCEPTION_H

#include <string>
#include <stdexcept>

class EntryNotFound : public std::runtime_error {
public:
    explicit EntryNotFound(const std::string &msg) : runtime_error(msg) {};
};

#endif //SHOPPING_LIST_EXCEPTION_H
