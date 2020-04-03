#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <string>
#include <utility>
#include <map>
#include <memory>
#include <algorithm>
#include <atomic>
#include "user.h"

class Entry {
    std::string title = "";
    std::atomic<int> amount = 1;
public:
    Entry();
    Entry(const Entry&);

    explicit Entry(std::string t);
    Entry(std::string t, int a);
    Entry &operator=(const Entry&);

    [[nodiscard]] std::string getIdentifier() const;

    [[nodiscard]] const std::string &getTitle() const;

    [[nodiscard]] int getAmount() const;

    void addAmount(int addition);
};

class List {
public:
    List() = default;
    ~List() = default;

    void add(const Entry &entry);
    void set(const Entry &entry);
    void set(const std::string &,const Entry &entry);
    void drop(const std::string&);

    [[nodiscard]] size_t size() const;
    [[nodiscard]] const Entry &get(const std::string &name) const;
    [[nodiscard]] const std::map<std::string, Entry> &get() const;

private:
    std::map<std::string, Entry> shoppingList = {};

};

class ListRepository {
    std::map<User, std::unique_ptr<List>> repo;
public:
    ListRepository() = default;
    ListRepository(ListRepository&&) = default;

    ListRepository(const ListRepository&) = delete;
    ListRepository &operator=(const ListRepository&) = delete;

    void init(const User &);
    [[nodiscard]] bool has(const User &) const;
    [[nodiscard]] List* find(const User &) const;
};

class EntryNotFound : public std::runtime_error {
public:
    explicit EntryNotFound(const std::string&);
};

#endif //LIST_LIST_H
