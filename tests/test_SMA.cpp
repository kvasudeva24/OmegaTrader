#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <OrderBook.hpp>
#include <Strategy.hpp>
#include <SMA.hpp>


TEST_CASE("Create and check size", "[SMA]"){
    SMA s1 = SMA(20);
    SMA s2 = SMA(40);
    s2 = s1;
    REQUIRE(s2.getSize() == s1.getSize());
    SMA s3(s2);
    REQUIRE(s2.getSize() == s3.getSize());
}

