#include "entry.h"

#include <algorithm>

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
