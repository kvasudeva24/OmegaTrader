#pragma once
#include "Order.hpp"
#include <map>
#include <queue>

class OrderBook {
private:
    int next_id_counter = 1;
    map<double, queue<Order>> ask_book;
    map<double, queue<Order>, greater<double>> bid_book;



public:
    void createBuyOrder(int q, double p);
    void insertBuyOrder(Order& order);

    //pass by reference because you want to change the value
    void checkAskBook(Order& order);

    Order& getBestAsk();
};