#ifndef SHOPPING_LIST_EXCEPTIONS_H
#define SHOPPING_LIST_EXCEPTIONS_H

#include <stdexcept>
#include <string>

class BadConfiguration: public std::runtime_error {
public:
    explicit BadConfiguration(const std::string &msg): std::runtime_error{msg} {};
};

class FileNotWritable: public BadConfiguration {
public:
    explicit FileNotWritable(const std::filesystem::path &file): BadConfiguration{"File " + file.string() + " cannot be written"} {};
};

#endif //SHOPPING_LIST_EXCEPTIONS_H
