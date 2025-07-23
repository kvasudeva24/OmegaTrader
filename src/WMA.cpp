#include "WMA.hpp"

WMA::WMA(int s){
    size = s;
}

WMA::WMA(const WMA& rhs){
    sliding_window = rhs.getSlidingWindow();
    size = rhs.getSize();
    moving_average = rhs.getMovingAverage();
}

WMA& WMA::operator=(const WMA& rhs){
    if(this != &rhs){
        sliding_window = rhs.getSlidingWindow();
        size = rhs.getSize();
        moving_average = rhs.getMovingAverage();
    }
    return *this;
}

double WMA::getMovingAverage() const {
    return moving_average;
}

int WMA::getSize() const {
    return size;
}

deque<double> WMA::getSlidingWindow() const {
    return sliding_window;
}

void WMA::onMarketData(double price, int quantity, OrderBook& Ob){
    if(sliding_window.size() != getSize()){
        sliding_window.push_back(price);
        updateMovingAverage();
        return;
    }
    double oldWMA = getMovingAverage();
    double last_price = sliding_window.back();
    sliding_window.pop_front();
    sliding_window.push_back(price);
    updateMovingAverage();
    double newWMA = getMovingAverage();

    if(last_price < oldWMA && price > newWMA){
        Ob.createBuyOrder(quantity, price);
    } else if (last_price > oldWMA && price < newWMA){
        Ob.createSellOrder(quantity, price);
    }

    return;
}

void WMA::updateMovingAverage(){
    int denom = (sliding_window.size() * (sliding_window.size()+1))/2;
    double count = 1;
    double average = 0.0;
    for(auto it = sliding_window.begin(); it!=sliding_window.end(); it++){
        double curr_price = *(it);
        average += (curr_price) * (count/denom);
        count++;
    }
    moving_average = average;
}

void WMA::setSize(int s){
    if(s > size){
        size = s;
    } else {
        while(sliding_window.size() > s){
            sliding_window.pop_front();
        }
        updateMovingAverage();
        size = s;
    }
}