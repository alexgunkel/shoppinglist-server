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
    filePtr << "foo:F27AB877EE002BAD7353436334E41AE847BE8B6F31F30CCF678BC7F1A4B9AD72\n"
        << "donald:B1E1ABA067B3AFC362AE553CB36E2DD9F7B50F0E62A21A18406B4E8C6EAD78C5\n" << std::endl;

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

TEST(HashingAlgorithmTest, testSha) {
    HashingAlgorithm algorithm;
    const auto result = algorithm.hashPassword(Password{"foo"});

    EXPECT_EQ("282B8395083D4E56DEC421843252560A7BC01376DFB7C1FF16C61016CDD259E3", result.get());
}
