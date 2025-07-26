#include "EMA.hpp"
#include <stdexcept>

EMA::EMA(int s) : size(s) {}

EMA::EMA(const EMA& rhs) {
    sliding_window = rhs.getSlidingWindow();
    moving_average = rhs.getMovingAverage();
    size = rhs.getSize();
}

EMA& EMA::operator=(const EMA& rhs) {
    if(this != &rhs){
        sliding_window = rhs.getSlidingWindow();
        moving_average = rhs.getMovingAverage();
        size = rhs.getSize();
    }
    return *this;
}

double EMA::getMovingAverage() const {
    return moving_average;
}

int EMA::getSize() const {
    return size;
}

deque<double> EMA::getSlidingWindow() const {
    return sliding_window;
}

double EMA::getK() {
    return k;
}

void EMA::onMarketData(double price, int quantity, OrderBook& Ob){
    if(sliding_window.size() != size){
        sliding_window.push_back(price);
        updateMovingAverage();
        return;
    }
    double oldEMA = getMovingAverage();
    sliding_window.pop_front();
    double last_price = sliding_window.back();
    sliding_window.push_back(price);
    updateMovingAverage();
    double newEMA = getMovingAverage();

    if(last_price < oldEMA && price > newEMA){
        Ob.createBuyOrder(quantity, price);
    } else if (last_price > oldEMA && price < newEMA){
        Ob.createSellOrder(quantity, price);
    }

    return;
}

void EMA::updateMovingAverage(){
    if(sliding_window.size() == 1){
        moving_average = *(sliding_window.begin());
        return;
    } else {
        double alpha = k/(getSize() + 1);
        moving_average = (moving_average * (1 - alpha)) + (alpha * sliding_window.back());
    }
}

void EMA::setSize(int s){
    if(s > size){
        throw invalid_argument("Cannot set window size to greater than current");
    } else {
        while(sliding_window.size() > s){
            sliding_window.pop_front();
        }
        updateMovingAverage();
        size = s;
    }
}