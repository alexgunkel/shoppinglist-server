#include "config/config_reader.h"

#include "test_config.h"

#include <gtest/gtest.h>

TEST(ConfigReaderTest, readFromFile) {
    std::filesystem::path configFile{std::string{FIXTURE_LOCATION} + "/simpleConfig.conf"};
    ConfigReader reader(configFile);

    EXPECT_EQ(ServerName{"localhost"}, reader.getServerConfig().getServer());
    EXPECT_EQ(Port{12345}, reader.getServerConfig().getPort());
    EXPECT_EQ(ProtocolScheme::http, reader.getServerConfig().getScheme());
}
