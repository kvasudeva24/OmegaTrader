#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <OrderBook.hpp>
#include <Strategy.hpp>
#include <EMA.hpp>




TEST_CASE("Create EMA and test private member variables", "[EMA]"){
    EMA e1 = EMA(25);
    REQUIRE(e1.getMovingAverage() == 0.0);
    REQUIRE(e1.getSize() == 25);
    REQUIRE(e1.getSlidingWindow().empty());
    REQUIRE(e1.getK() == 2);
}

TEST_CASE("Moving average works correctly", "[EMA]"){
    OrderBook ob;
    EMA e1 = EMA(3);

    e1.onMarketData(10.0, 1, ob);
    REQUIRE(e1.getMovingAverage() == 10.0);
    e1.onMarketData(20.0, 1, ob);
    REQUIRE(e1.getMovingAverage() == 15.0);
    e1.onMarketData(30.0, 1, ob);
    REQUIRE(e1.getMovingAverage() == 22.5);
}

