// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <OrderBook.hpp>
#include <Strategy.hpp>
#include <SMA.hpp>

OrderBook ob;


TEST_CASE("Create and check size", "[SMA]"){
    SMA s1 = SMA(20);
    SMA s2 = SMA(40);
    s2 = s1;
    REQUIRE(s2.getSize() == s1.getSize());
    SMA s3(s2);
    REQUIRE(s2.getSize() == s3.getSize());
}

TEST_CASE("SMA initializes correctly", "[SMA]") {
    SMA sma(10);
    REQUIRE(sma.getSize() == 10);
    REQUIRE(sma.getMovingAverage() == 0.0);
    REQUIRE(sma.getSlidingWindow().empty());
}

TEST_CASE("SMA updates moving average correctly", "[SMA]") {
    SMA sma(3);
    
    sma.onMarketData(10.0, 1, ob);
    REQUIRE(sma.getMovingAverage() ==  (10.0));

    sma.onMarketData(20.0, 1, ob);
    REQUIRE(sma.getMovingAverage() ==  (15.0));

    sma.onMarketData(30.0, 1, ob);
    REQUIRE(sma.getMovingAverage() ==  (20.0));

    // Now window is full, next addition should drop 10.0
    sma.onMarketData(40.0, 1, ob);
    // Now window = [20.0, 30.0, 40.0]
    REQUIRE(sma.getMovingAverage() ==  (30.0));
}

TEST_CASE("SMA sliding window maintains correct size", "[SMA]") {
    SMA sma(2);

    sma.onMarketData(100.0, 1, ob);
    sma.onMarketData(200.0, 1, ob);
    REQUIRE(sma.getSlidingWindow().size() == 2);

    sma.onMarketData(300.0, 1, ob);
    REQUIRE(sma.getSlidingWindow().size() == 2); // oldest (100.0) dropped
    REQUIRE(sma.getSlidingWindow().front() ==  (200.0));
    REQUIRE(sma.getSlidingWindow().back() ==  (300.0));
}

TEST_CASE("SMA setSize resets sliding window and moving average", "[SMA]") {
    SMA sma(3);
    sma.onMarketData(10, 1, ob);
    sma.onMarketData(20, 1, ob);
    REQUIRE(sma.getMovingAverage() ==  (15.0));
    REQUIRE(sma.getSlidingWindow().size() == 2);

    sma.setSize(1); // should clear old data
    REQUIRE(sma.getSize() == 1);
    REQUIRE(sma.getSlidingWindow().size() == 1);
    REQUIRE(sma.getMovingAverage() ==  (20));
}

TEST_CASE("SMA handles multiple insertions with same price", "[SMA]") {
    SMA sma(4);
    sma.onMarketData(5, 1, ob);
    sma.onMarketData(5, 1, ob);
    sma.onMarketData(5, 1, ob);
    sma.onMarketData(5, 1, ob);

    REQUIRE(sma.getMovingAverage() ==  (5.0));
    REQUIRE(sma.getSlidingWindow().size() == 4);
}

