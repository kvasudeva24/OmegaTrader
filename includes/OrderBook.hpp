#pragma once
#include "Order.hpp"
#include <map>
#include <list>
#include <memory>

class OrderBook {
private:
    int next_id_counter = 1;
    map<double, list<unique_ptr<Order>>> ask_book;
    map<double, list<unique_ptr<Order>>, greater<double>> bid_book;

    unordered_map<int, tuple<double, Side, list<unique_ptr<Order>>::iterator>> id_map;


public:
    OrderBook() = default;
    OrderBook(const OrderBook& rhs) = delete;
    OrderBook& operator=(const OrderBook& rhs) = delete;

    void createBuyOrder(int q, double p);
    void insertBuyOrder(unique_ptr<Order> ptr);
    void checkAskBook(unique_ptr<Order> ptr);
    Order& getBestAsk();

    void createSellOrder(int q, double p);
    void insertSellOrder(unique_ptr<Order> ptr);
    void checkBidBook(unique_ptr<Order> ptr);
    Order& getBestBid();

    void cancelOrder(int id);

    void printBidBook();
    void printAskBook();

    const map<double, list<unique_ptr<Order>>, greater<double>>& getBidBook() const;

    const map<double, list<unique_ptr<Order>>>& getAskBook() const;
};