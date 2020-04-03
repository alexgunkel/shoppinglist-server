#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <string>
#include <utility>
#include <map>
#include <memory>
#include "user.h"
#include "entry.h"


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

#endif //LIST_LIST_H
