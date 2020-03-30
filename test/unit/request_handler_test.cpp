#include <gtest/gtest.h>

#include "RequestHandler.h"

TEST(RequestHandlerTest, testEntry) {
    EXPECT_EQ("foo", Route::fromPath("/foo/bar/12").list);
    EXPECT_EQ("bar", Route::fromPath("/foo/bar/12").entry);
}

TEST(RequestHandlerTest, testFailure) {
    EXPECT_THROW(Route::fromPath(""), std::runtime_error);
    EXPECT_THROW(Route::fromPath("/foo"), std::runtime_error);
    EXPECT_THROW(Route::fromPath("/"), std::runtime_error);
}

TEST(RequestHandlerTest, testHandleGet) {
    List empty;
    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));

    EXPECT_THROW(RequestHandler::handleGet(req, &empty), EntryNotFound);
}
