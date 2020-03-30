#include "List.h"

void List::add(const Entry &entry) {
    auto found = shoppingList.find(entry.getTitle());
    if (found != shoppingList.end()) {
        found->second.addAmount(entry.getAmount());
    } else {
        shoppingList[entry.getTitle()] = entry;
    }
}

const Entry &List::get(const std::string &name) const {
    const auto found = shoppingList.find(name);

    if (found == shoppingList.end()) {
        throw EntryNotFound{"no entry with name " + name};
    }

    return found->second;
}

EntryNotFound::EntryNotFound(const std::string &msg) : runtime_error(msg){

}
