#pragma once
#include "Order.hpp"
#include <map>
#include <list>

class OrderBook {
private:
    int next_id_counter = 1;
    map<double, list<Order>> ask_book;
    map<double, list<Order>, greater<double>> bid_book;

    unordered_map<int, tuple<double, Side, list<Order>::iterator>> id_map;



public:
    void createBuyOrder(int q, double p);
    void insertBuyOrder(Order& order);

    //pass by reference because you want to change the value
    void checkAskBook(Order& order);

    Order& getBestAsk();

    void createSellOrder(int q, double p);
    void insertSellOrder(Order& order);
    void checkBidBook(Order& order);
    Order& getBestBid();

    void cancelOrder(int id);

    void printBidBook();
    void printAskBook();
};