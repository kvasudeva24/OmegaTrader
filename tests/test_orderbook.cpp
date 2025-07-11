#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <OrderBook.hpp>


TEST_CASE("Create and insert Buy Order", "[buy]") {
    OrderBook ob;
    ob.createBuyOrder(100, 10.0);
    Order& bestBid = ob.getBestBid();
    REQUIRE(bestBid.getPrice() == 10.0);
    REQUIRE(bestBid.getQuantity() == 100);
    REQUIRE(bestBid.getSide() == Side::BUY);
}

TEST_CASE("Create and insert Sell Order", "[sell]") {
    OrderBook ob;
    ob.createSellOrder(50, 11.0);
    Order& bestAsk = ob.getBestAsk();
    REQUIRE(bestAsk.getPrice() == 11.0);
    REQUIRE(bestAsk.getQuantity() == 50);
    REQUIRE(bestAsk.getSide() == Side::SELL);
}

TEST_CASE("Buy matches with Sell", "[match]") {
    OrderBook ob;
    ob.createSellOrder(30, 10.0);
    ob.createBuyOrder(30, 10.0);

    // Since the order should match, there should be nothing in the books
    REQUIRE_THROWS_AS(ob.getBestAsk(), std::out_of_range);
    REQUIRE_THROWS_AS(ob.getBestBid(), std::out_of_range);
}

TEST_CASE("Cancel an Order", "[cancel]") {
    OrderBook ob;
    ob.createBuyOrder(20, 9.5);
    Order& bid = ob.getBestBid();
    int id = bid.getID();

    ob.cancelOrder(id);
    REQUIRE_THROWS_AS(ob.getBestBid(), std::out_of_range);
}

TEST_CASE("Partial match", "[partial]") {
    OrderBook ob;
    ob.createSellOrder(50, 8.0);
    ob.createBuyOrder(30, 8.0);

    Order& ask = ob.getBestAsk();
    REQUIRE(ask.getQuantity() == 20);
    REQUIRE(ask.getPrice() == 8.0);
}