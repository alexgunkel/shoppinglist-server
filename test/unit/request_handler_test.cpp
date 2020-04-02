#include <gtest/gtest.h>
#include <json_decorator.h>

#include "request_handler.h"

#include "../mocks/authentication_mocks.h"

TEST(RequestHandlerTest, testEntry) {
    EXPECT_EQ("foo", Route::fromPath("/foo/bar/12").user.get());
    EXPECT_EQ("bar", Route::fromPath("/foo/bar/12").entry.value());
    EXPECT_EQ("foo", Route::fromPath("/foo").user.get());
    EXPECT_EQ(false, Route::fromPath("/foo").entry.has_value());
}

TEST(RequestHandlerTest, testFailure) {
    EXPECT_THROW(Route::fromPath(""), std::runtime_error);
    EXPECT_THROW(Route::fromPath("/"), std::runtime_error);
}

TEST(RequestHandlerTest, testGetUnAuthorized) {
    auto listRepo = std::make_shared<ListRepository>();
    auto authService = std::make_unique<AuthenticationCheckInterfaceMock>();
    ON_CALL(*authService, check).WillByDefault([](auto req) {return false;});
    RequestHandler requestHandler{std::move(authService), listRepo};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/guest"));
    req.headers().add(requestHandler.authorizationField.get(), "test");

    requestHandler.handleGet(req);

    ASSERT_EQ(web::http::status_codes::Unauthorized, req.get_response().get().status_code());
    ASSERT_FALSE(req.get_response().get().body().is_valid());
}

TEST(RequestHandlerTest, testGetAll) {
    auto listRepo = std::make_shared<ListRepository>();
    listRepo->init(User{"guest"});
    listRepo->find(User{"guest"})->add({"bar", 3});
    listRepo->find(User{"guest"})->add({"foo", 2});
    auto authService = std::make_unique<AuthenticationCheckInterfaceMock>();
    ON_CALL(*authService, check).WillByDefault([](auto req) {return true;});
    RequestHandler requestHandler{std::move(authService), listRepo};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/guest"));
    req.headers().add(requestHandler.authorizationField.get(), "test");


    requestHandler.handleGet(req);

    ASSERT_EQ(web::http::status_codes::OK, req.get_response().get().status_code());
    ASSERT_TRUE(req.get_response().get().body().is_valid());

    const auto result = req.get_response().get().extract_json().get();

    EXPECT_EQ(2, result.size());
    EXPECT_EQ("bar", result.at(0).as_object().at("title").as_string());
}

TEST(RequestHandlerTest, testHandleGetNotFound) {
    auto listRepo = std::make_shared<ListRepository>();
    listRepo->init(User{"foo"});
    auto authService = std::make_unique<AuthenticationCheckInterfaceMock>();
    ON_CALL(*authService, check).WillByDefault([](auto req) {return true;});
    RequestHandler requestHandler{std::move(authService), listRepo};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));
    req.headers().add(requestHandler.authorizationField.get(), "test");

    EXPECT_NO_THROW(requestHandler.handleGet(req));

    auto resp = req.get_response().get();
    EXPECT_EQ(web::http::status_codes::NotFound, resp.status_code());
}

TEST(RequestHandlerTest, testHandleGetFound) {
    auto listRepo = std::make_shared<ListRepository>();
    listRepo->init(User{"foo"});
    listRepo->find(User{"foo"})->add({"bar", 1});
    auto authService = std::make_unique<AuthenticationCheckInterfaceMock>();
    ON_CALL(*authService, check).WillByDefault([](auto req) {return true;});
    RequestHandler requestHandler{std::move(authService), listRepo};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));
    req.headers().add(requestHandler.authorizationField.get(), "test");

    EXPECT_NO_THROW(requestHandler.handleGet(req));

    const auto resp = req.get_response().get();
    EXPECT_EQ(web::http::status_codes::OK, resp.status_code());
    EXPECT_EQ(1, resp.extract_json().get()["amount"].as_integer());
}

TEST(RequestHandlerTest, testHandlePost) {
    auto listRepo = std::make_shared<ListRepository>();
    listRepo->init(User{"foo"});
    auto authService = std::make_unique<AuthenticationCheckInterfaceMock>();
    ON_CALL(*authService, check).WillByDefault([](auto req) {return true;});
    RequestHandler requestHandler{std::move(authService), listRepo};

    const Entry b{"bar", 2};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));
    req.set_body(EntryJsonDecorator{b}.toJson());
    req.headers().add(requestHandler.authorizationField.get(), "test");

    ASSERT_NO_THROW(requestHandler.handlePost(req));

    EXPECT_GE(web::http::status_codes::Accepted, req.get_response().get().status_code());
    EXPECT_EQ(1, listRepo->find(User{"foo"})->size());
    EXPECT_EQ(2, listRepo->find(User{"foo"})->get("bar").getAmount());
}

TEST(RequestHandlerTest, testHandlePostWithError) {
    auto listRepo = std::make_shared<ListRepository>();
    listRepo->init(User{"foo"});
    auto authService = std::make_unique<AuthenticationCheckInterfaceMock>();
    ON_CALL(*authService, check).WillByDefault([](auto req) {return true;});
    RequestHandler requestHandler{std::move(authService), listRepo};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));
    req.headers().add(requestHandler.authorizationField.get(), "test");

    ASSERT_NO_THROW(requestHandler.handlePost(req));

    EXPECT_EQ(web::http::status_codes::BadRequest, req.get_response().get().status_code());
}
