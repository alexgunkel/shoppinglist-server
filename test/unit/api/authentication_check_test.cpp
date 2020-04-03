#include "api/authentication_check.h"

#include <gtest/gtest.h>
#include <cpprest/asyncrt_utils.h>

TEST(AuthenticationRepositoryTest, testAuthentication) {
    AuthenticationRepository repo{std::make_unique<HashingAlgorithm>()};

    repo.addUser(User{"foo"}, Password{"bar"});

    EXPECT_TRUE(repo.checkUser(User{"foo"}, Password{"bar"}));
    EXPECT_FALSE(repo.checkUser(User{"foo"}, Password{"foo"}));
}

TEST(AuthenticationCheck, testCheck) {
    auto repo = std::make_unique<AuthenticationRepository>(std::make_unique<HashingAlgorithm>());
    repo->addUser(User{"foo"}, Password{"bar"});

    AuthenticationCheck check{std::move(repo)};

    std::vector<unsigned char > valid = {'f', 'o', 'o', ':', 'b', 'a', 'r'};
    std::vector<unsigned char > inValid = {'b', 'a', 'r', ':', 'f', 'o', 'o'};
    EXPECT_TRUE(check.check(Base64(utility::conversions::to_base64(valid))));
    EXPECT_FALSE(check.check(Base64(utility::conversions::to_base64(inValid))));
}

TEST(AuthenticationRepository, testReadfile) {
    auto file = std::tmpnam(nullptr);

    std::ofstream filePtr;
    filePtr.open(file);
    filePtr << "foo:bar\n" << "donald:duck\n" << std::endl;

    AuthenticationRepository repository{std::make_unique<HashingAlgorithm>()};
    repository.readFile(std::string(file));
    filePtr.close();

    EXPECT_TRUE(repository.checkUser(User{"foo"}, Password{"bar"}));
    EXPECT_TRUE(repository.checkUser(User{"donald"}, Password{"duck"}));
    EXPECT_FALSE(repository.checkUser(User{"foo"}, Password{"duck"}));
    EXPECT_FALSE(repository.checkUser(User{"donald"}, Password{"bar"}));
}

TEST(AuthenticationRepository, testReadFileFailure) {
    auto file = std::tmpnam(nullptr);

    AuthenticationRepository repository{std::make_unique<HashingAlgorithm>()};
    EXPECT_ANY_THROW(repository.readFile(std::string{file}));
}
