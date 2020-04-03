#ifndef SHOPPING_LIST_EXCEPTION_H
#define SHOPPING_LIST_EXCEPTION_H

#include <filesystem>
#include <stdexcept>
#include <utility>

class InvalidConfigFile: public std::runtime_error {
    std::filesystem::path givenPath;

public:
    InvalidConfigFile(const std::string &msg, std::filesystem::path p): std::runtime_error{msg}, givenPath{std::move(p)} {};
};

#endif //SHOPPING_LIST_EXCEPTION_H
