#include "OrderBook.hpp"

class Strategy {

    virtual void onMarketData(double price, int quantity, OrderBook& ob) = 0;
    virtual ~Strategy() = default;

};