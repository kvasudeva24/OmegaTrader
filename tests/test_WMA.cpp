#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <OrderBook.hpp>
#include <Strategy.hpp>
#include <WMA.hpp>

OrderBook ob;


TEST_CASE("Create and check size", "[WMA]"){
    WMA s1 = WMA(20);
    WMA s2 = WMA(40);
    s2 = s1;
    REQUIRE(s2.getSize() == s1.getSize());
    WMA s3(s2);
    REQUIRE(s2.getSize() == s3.getSize());
}

TEST_CASE("WMA initializes correctly", "[WMA]") {
    WMA wma(10);
    REQUIRE(wma.getSize() == 10);
    REQUIRE(wma.getMovingAverage() == 0.0);
    REQUIRE(wma.getSlidingWindow().empty());
}

TEST_CASE("WMA updates moving average correctly", "[WMA]") {
    WMA wma(3);
    
    wma.onMarketData(10.0, 1, ob);
    REQUIRE(wma.getMovingAverage() ==  (10.0));

    wma.onMarketData(20.0, 1, ob);
    REQUIRE(int(wma.getMovingAverage()) ==  (16));

    wma.onMarketData(30.0, 1, ob);
    REQUIRE(int(wma.getMovingAverage()) ==  (23));

    // Now window is full, next addition should drop 10.0
    wma.onMarketData(40.0, 1, ob);
    // Now window = [20.0, 30.0, 40.0]
    REQUIRE(int(wma.getMovingAverage()) ==  (33));
}

TEST_CASE("WMA sliding window maintains correct size", "[WMA]") {
    WMA wma(2);

    wma.onMarketData(100.0, 1, ob);
    wma.onMarketData(200.0, 1, ob);
    REQUIRE(wma.getSlidingWindow().size() == 2);

    wma.onMarketData(300.0, 1, ob);
    REQUIRE(wma.getSlidingWindow().size() == 2); // oldest (100.0) dropped
    REQUIRE(wma.getSlidingWindow().front() ==  (200.0));
    REQUIRE(wma.getSlidingWindow().back() ==  (300.0));
}

TEST_CASE("WMA setSize resets sliding window and moving average", "[WMA]") {
    WMA wma(3);
    wma.onMarketData(10, 1, ob);
    wma.onMarketData(20, 1, ob);
    REQUIRE(int(wma.getMovingAverage()) ==  (16));
    REQUIRE(wma.getSlidingWindow().size() == 2);

    wma.setSize(1); // should clear old data
    REQUIRE(wma.getSize() == 1);
    REQUIRE(wma.getSlidingWindow().size() == 1);
    REQUIRE(wma.getMovingAverage() ==  (20));
}

TEST_CASE("WMA handles multiple insertions with same price", "[WMA]") {
    WMA wma(4);
    wma.onMarketData(5, 1, ob);
    wma.onMarketData(5, 1, ob);
    wma.onMarketData(5, 1, ob);
    wma.onMarketData(5, 1, ob);

    REQUIRE(wma.getMovingAverage() ==  (5.0));
    REQUIRE(wma.getSlidingWindow().size() == 4);
}

