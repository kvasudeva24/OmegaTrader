#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <OrderBook.hpp>
#include <Strategy.hpp>
#include <EMA.hpp>
#include <queue>


OrderBook ob;


TEST_CASE("Create EMA and test private member variables", "[WMA]"){
    EMA e1 = EMA(25);
    REQUIRE(e1.getMovingAverage() == 0.0);
    REQUIRE(e1.getSize() == 25);
    REQUIRE(e1.getSlidingWindow() == deque<double>());
    REQUIRE(e1.getK() == 2);
}