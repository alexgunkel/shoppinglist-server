#ifndef SHOPPING_LIST_ENTRY_H
#define SHOPPING_LIST_ENTRY_H

#include <string>
#include <atomic>

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

#endif //SHOPPING_LIST_ENTRY_H
