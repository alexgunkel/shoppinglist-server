#include <gtest/gtest.h>

#include "config/server_config.h"

TEST(ServerConfigurationTest, testInstantiate) {
    ServerConfig serverConfig{ServerName{"test"}, Port{98}};

    EXPECT_EQ("test", serverConfig.getServer().get());
    EXPECT_EQ(98, serverConfig.getPort().get());
    EXPECT_EQ(ProtocolScheme::http, serverConfig.getScheme());
}

TEST(ServerConfigurationTest, testAddress) {
    EXPECT_EQ("http://localhost:123",ServerConfig(ServerName{"localhost"}, Port{123}).getAddress());
    EXPECT_EQ("https://localhost:123",ServerConfig(ServerName{"localhost"}, Port{123}, ProtocolScheme::https).getAddress());
}
