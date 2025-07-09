#pragma once
#include <string>

using namespace std;

enum class Side {
    BUY,
    SELL
};


class Order {

private:
    int id;
    int quantity;
    double price;
    Side side;

public:
    //default
    Order(int i, int q, double p, Side s);

    //copy data but have unique id
    Order(int i, const Order& other);

    //copy assignment 
    Order& operator=(const Order& other);

    //move
    Order(Order&& other) = default;

    //move assignment
    Order& operator=(Order&& other) = default;

    
    //getter and setters
    int getID() const;
    int getQuantity() const;
    double getPrice() const;
    Side getSide() const;

    void setQuantity(int q);
    void setPrice(double p);

    string toString() const;

};