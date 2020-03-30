#ifndef LIST_LIST_H
#define LIST_LIST_H

#include <string>
#include <utility>
#include <map>

enum class ProtocolScheme {
    http,
    https,
};

class ListConfig {
private:
    std::string server;
    int port;
    ProtocolScheme protocolScheme;

public:
    ListConfig(std::string serverName, int port, ProtocolScheme scheme = ProtocolScheme::http)
        : server{std::move(serverName)}
        , port{port}
        , protocolScheme{scheme}
    {};

    [[nodiscard]] const std::string &getServer() const {
        return server;
    }

    [[nodiscard]] const int &getPort() const {
        return port;
    }

    [[nodiscard]] std::string getScheme() const {
        return protocolScheme == ProtocolScheme::http ? "http" : "https";
    }
};

class Entry {
    std::string title;
    int amount = 1;
public:
    explicit Entry(std::string t): title{std::move(t)} {};
    explicit Entry(std::string t, int a): title{std::move(t)}, amount{a} {};

    [[nodiscard]] const std::string &getTitle() const {
        return title;
    };

    [[nodiscard]] int getAmount() const {
        return amount;
    };
};

class List {
public:
    explicit List(ListConfig config);
    ~List();

    [[nodiscard]] std::string Address() const;

private:
    ListConfig config;
    std::map<int, Entry> shoppingList = {};

};


#endif //LIST_LIST_H
