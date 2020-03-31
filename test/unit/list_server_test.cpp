#include <gtest/gtest.h>

#include "list_server.h"

TEST(ServerConfigurationTest, testInstantiate) {
    ListConfig listConfig{"test", 98};

    EXPECT_EQ("test", listConfig.getServer());
    EXPECT_EQ(98, listConfig.getPort());
    EXPECT_EQ("http", listConfig.getScheme());
}

TEST(ServerConfigurationTest, testAddress) {
    EXPECT_EQ("http://localhost:123",ListConfig("localhost", 123).getAddress());
    EXPECT_EQ("https://localhost:123",ListConfig("localhost", 123, ProtocolScheme::https).getAddress());
}
