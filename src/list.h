#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <string>
#include <utility>
#include <map>

class Entry {
    std::string title = "";
    int amount = 1;
public:
    Entry() = default;
    explicit Entry(std::string t): title{std::move(t)} {};
    Entry(std::string t, int a): title{std::move(t)}, amount{a} {};

    [[nodiscard]] const std::string &getTitle() const {
        return title;
    };

    [[nodiscard]] int getAmount() const {
        return amount;
    };

    void addAmount(int addition) {
        amount += addition;
    }

    bool operator<(const Entry &rhs) const {
        return title < rhs.title;
    }

    bool operator>(const Entry &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Entry &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Entry &rhs) const {
        return !(*this < rhs);
    }
};

class List {
public:
    List() = default;
    ~List() = default;

    void add(const Entry &entry);
    [[nodiscard]] size_t size() const;
    [[nodiscard]] const Entry &get(const std::string &name) const;
    [[nodiscard]] const std::map<std::string, Entry> &get() const;

private:
    std::map<std::string, Entry> shoppingList = {};

};

class EntryNotFound : public std::runtime_error {
public:
    explicit EntryNotFound(const std::string&);
};

#endif //LIST_LIST_H
