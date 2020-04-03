#include "list.h"

void List::add(const Entry &entry) {
    auto found = shoppingList.find(entry.getIdentifier());
    if (found != shoppingList.end()) {
        found->second.addAmount(entry.getAmount());
    } else {
        shoppingList[entry.getIdentifier()] = entry;
    }
}

const Entry &List::get(const std::string &name) const {
    const auto found = shoppingList.find(name);

    if (found == shoppingList.end()) {
        throw EntryNotFound{"no entry with name " + name};
    }

    return found->second;
}

size_t List::size() const {
    return shoppingList.size();
}

const std::map<std::string, Entry> &List::get() const {
    return shoppingList;
}

void List::set(const Entry &entry) {
    shoppingList[entry.getIdentifier()] = entry;
}

void List::set(const std::string &identifier, const Entry &entry) {
    shoppingList[identifier] = entry;
}

void List::drop(const std::string &identifier) {
    if (shoppingList.find(identifier) == shoppingList.end()) {
        throw EntryNotFound("no entry found for " + identifier);
    }

    shoppingList.erase(identifier);
}

EntryNotFound::EntryNotFound(const std::string &msg) : runtime_error(msg){

}

Entry::Entry() = default;

Entry::Entry(std::string t): title{std::move(t)} {};

Entry::Entry(std::string t, int a): title{std::move(t)}, amount{a} {};

std::string Entry::getIdentifier() const {
    std::string res = title;

    std::transform(
            res.begin(),
            res.end(),
            res.begin(),
            [](const unsigned char c) -> unsigned char {
                if (c <= 'z' && c >= 'A') {
                    return std::tolower(c);
                }

                return '-';
            }
    );

    return res;
};

void Entry::addAmount(int addition) {
    amount += addition;
}

const std::string &Entry::getTitle() const {
    return title;
};

int Entry::getAmount() const {
    return amount;
}

Entry &Entry::operator=(const Entry &other) {
    if (&other == this) {
        return *this;
    }

    amount.store(other.amount);
    title = other.title;

    return *this;
}

Entry::Entry(const Entry &other) {
    amount.store(other.getAmount());
    title = other.title;
};

void ListRepository::init(const User &user) {
    repo[user] = std::make_unique<List>();
}

List *ListRepository::find(const User &user) const {
    return repo.at(user).get();
}

bool ListRepository::has(const User &user) const {
    return repo.find(user) != repo.end();
}
