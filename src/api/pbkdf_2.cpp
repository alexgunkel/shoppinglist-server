#include "pbkdf_2.h"

#include <cryptopp/sha.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/hex.h>

#include <utility>

using CryptoPP::byte;
using CryptoPP::SHA256;

Pbkdf2::Pbkdf2(const Password &pwd, std::string salt): password{pwd}, _salt{std::move(salt)} {
}

PasswordHash Pbkdf2::getHash() const {
    byte *pwd, *s;
    pwd = new byte[password.get().length()];
    s = new byte[_salt.length()];
    std::transform(password.get().begin(), password.get().end(), pwd, [](const auto& in) -> byte { return byte(in);});
    std::transform(_salt.begin(), _salt.end(), s, [](const auto& in) -> byte { return byte(in);});

    byte derivedBytes[SHA256::DIGESTSIZE];
    CryptoPP::PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
    byte unused{0};

    pbkdf.DeriveKey(derivedBytes, sizeof(derivedBytes), unused, pwd, password.get().length(), s, strlen((const char*)s), 1024);

    delete [] pwd;
    delete [] s;

    std::string result;
    auto sink = new CryptoPP::StringSink{result};
    CryptoPP::HexEncoder encoder{sink};
    encoder.Put(derivedBytes, sizeof(derivedBytes));
    encoder.MessageEnd();
    return PasswordHash{result};
}

bool Pbkdf2::checkHash(const PasswordHash &hash) const {
    return hash == getHash();
}
