#ifndef LIST_AUTHENTICATION_MOCKS_H
#define LIST_AUTHENTICATION_MOCKS_H

#include "api/authentication_check.h"
#include <gmock/gmock.h>

class AuthenticationCheckInterfaceMock: public AuthenticationCheckInterface {
public:
    MOCK_METHOD(bool, check, (const Base64&), (const));
};

#endif //LIST_AUTHENTICATION_MOCKS_H
