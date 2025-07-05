#include <catch2/catch_test_macros.hpp>
#include "Order.hpp"

TEST_CASE("Order constructor sets fields correctly", "[Order]") {
    Order o(1, 100, 42.5, Side::BUY);
    REQUIRE(o.getID() == 1);
    REQUIRE(o.getQuantity() == 100);
    REQUIRE(o.getPrice() == (42.5));
    REQUIRE(o.getSide() == Side::BUY);
}

TEST_CASE("Copy constructor with new ID copies fields correctly", "[Order]") {
    Order original(5, 200, 99.9, Side::SELL);
    Order copy(10, original);
    REQUIRE(copy.getID() == 10); // New ID
    REQUIRE(copy.getQuantity() == 200);
    REQUIRE(copy.getPrice() == (99.9));
    REQUIRE(copy.getSide() == Side::SELL);
}

TEST_CASE("Copy assignment operator copies values (ID stays the same)", "[Order]") {
    Order a(2, 50, 33.3, Side::BUY);
    Order b(3, 80, 10.0, Side::SELL);
    a = b;
    REQUIRE(a.getID() == 2); // ID does not change
    REQUIRE(a.getQuantity() == 80);
    REQUIRE(a.getPrice() == (10.0));
    REQUIRE(a.getSide() == Side::SELL);
}

TEST_CASE("Move constructor transfers data", "[Order]") {
    Order original(8, 300, 75.0, Side::BUY);
    Order moved(std::move(original));
    REQUIRE(moved.getID() == 8);
    REQUIRE(moved.getQuantity() == 300);
    REQUIRE(moved.getPrice() == (75.0));
    REQUIRE(moved.getSide() == Side::BUY);
}

TEST_CASE("Move assignment transfers data", "[Order]") {
    Order source(6, 120, 15.5, Side::SELL);
    Order dest(7, 999, 999.9, Side::BUY);
    dest = std::move(source);
    REQUIRE(dest.getID() == 6);
    REQUIRE(dest.getQuantity() == 120);
    REQUIRE(dest.getPrice() == (15.5));
    REQUIRE(dest.getSide() == Side::SELL);
}

TEST_CASE("Setters modify quantity and price", "[Order]") {
    Order o(4, 10, 5.0, Side::BUY);
    o.setQuantity(25);
    o.setPrice(8.75);
    REQUIRE(o.getQuantity() == 25);
    REQUIRE(o.getPrice() == (8.75));
}