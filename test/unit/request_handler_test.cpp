#include <gtest/gtest.h>
#include <json_decorator.h>

#include "request_handler.h"

TEST(RequestHandlerTest, testEntry) {
    EXPECT_EQ("foo", Route::fromPath("/foo/bar/12").list);
    EXPECT_EQ("bar", Route::fromPath("/foo/bar/12").entry.value());
    EXPECT_EQ("foo", Route::fromPath("/foo").list);
    EXPECT_EQ(false, Route::fromPath("/foo").entry.has_value());
}

TEST(RequestHandlerTest, testFailure) {
    EXPECT_THROW(Route::fromPath(""), std::runtime_error);
    EXPECT_THROW(Route::fromPath("/"), std::runtime_error);
}

TEST(RequestHandlerTest, testGetAll) {
    List list;
    list.add({"bar", 3});
    list.add({"for", 2});

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/guest"));

    RequestHandler::handleGet(req, &list);

    ASSERT_EQ(web::http::status_codes::OK, req.get_response().get().status_code());
    ASSERT_TRUE(req.get_response().get().body().is_valid());

    const auto result = req.get_response().get().extract_json().get();

    EXPECT_EQ(2, result.size());
    EXPECT_EQ("bar", result.at(0).as_object().at("title").as_string());
}

TEST(RequestHandlerTest, testHandleGetNotFound) {
    List empty;
    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));

    EXPECT_NO_THROW(RequestHandler::handleGet(req, &empty));

    auto resp = req.get_response().get();
    EXPECT_EQ(web::http::status_codes::NotFound, resp.status_code());
}

TEST(RequestHandlerTest, testHandleGetFound) {
    List list;
    list.add({"bar", 1});

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));

    EXPECT_NO_THROW(RequestHandler::handleGet(req, &list));

    const auto resp = req.get_response().get();
    EXPECT_EQ(web::http::status_codes::OK, resp.status_code());
    EXPECT_EQ(1, resp.extract_json().get()["amount"].as_integer());
}

TEST(RequestHandlerTest, testHandlePost) {
    List list;

    const Entry b{"bar", 2};

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));
    req.set_body(EntryJsonDecorator{b}.toJson());

    ASSERT_NO_THROW(RequestHandler::handlePost(req, &list));

    EXPECT_GE(web::http::status_codes::Accepted, req.get_response().get().status_code());
    EXPECT_EQ(1, list.size());
    EXPECT_EQ(2, list.get("bar").getAmount());
}

TEST(RequestHandlerTest, testHandlePostWithError) {
    List list;

    web::http::http_request req;
    req.set_request_uri(web::uri("http://localhost/foo/bar"));

    ASSERT_NO_THROW(RequestHandler::handlePost(req, &list));

    EXPECT_EQ(web::http::status_codes::BadRequest, req.get_response().get().status_code());
}
