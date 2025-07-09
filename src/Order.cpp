#include "Order.hpp"

Order::Order(int i, int q, double p, Side s) : id(i), quantity(q), price(p), side(s) {}

//make a new order after one already exists
Order::Order(int i, const Order& other){
    id = i;
    quantity = other.getQuantity();
    price = other.getPrice();
    side = other.getSide();
}

//copy an order but keep the id the same after initialization
Order& Order::operator=(const Order& other){
    if(this != &other){
        quantity = other.getQuantity();
        price = other.getPrice();
        side = other.getSide();
    }
    return *this;
}

int Order::getID() const {
    return id;
}

int Order::getQuantity() const {
    return quantity;
}

double Order::getPrice() const {
    return price;
}

Side Order::getSide() const {
    return side;
}

void Order::setQuantity(int q){
    quantity = q;
    return;
}

void Order::setPrice(double p){
    price = p;
    return;
}

string Order::toString() const {
    string ret = "";
    switch(side){
        case (Side::BUY):
            ret = "Buy";
            break;
        case (Side::SELL):
            ret = "Sell";
            break;
        default:
            ret = "Unknown";
            break;
    }


    return "ID: " + to_string(id) + " -- Quantity: " + to_string(quantity) + " -- Price: " + to_string(price) + " -- Side: " + ret;
}