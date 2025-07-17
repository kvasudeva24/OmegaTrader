#include "SMA.hpp"
#include <numeric>



SMA::SMA(int s) : size(s){}

SMA::SMA(const SMA& rhs){
    sliding_window = rhs.getSlidingWindow();
    size = rhs.getSize();
    moving_average = rhs.getMovingAverage();
}

SMA& SMA::operator=(const SMA& rhs){
    if(this != &rhs){
        sliding_window = rhs.getSlidingWindow();
        size = rhs.getSize();
        moving_average = rhs.getMovingAverage();
    }
    return *this;
}

void SMA::setSize(int s){
    if(s > size){
        size = s;
    } else {
        int n = 0;
        deque<double> curr;
        while(n<s){
            curr.push_front(sliding_window.front());
            sliding_window.pop_front();
            n++;
        }
        updateMovingAverage();
        sliding_window = curr;
        size = s;
    }
}

double SMA::getMovingAverage() const {
    return moving_average;
}

int SMA::getSize() const {
    return size;
}

deque<double> SMA::getSlidingWindow() const {
    return sliding_window;
}

void SMA::updateMovingAverage() {
    moving_average = accumulate(sliding_window.begin(), sliding_window.end(), 0.0);
    moving_average /= sliding_window.size();
}

void SMA::onMarketData(double price, int quantity, OrderBook& Ob) {
    if(sliding_window.size() != getSize()){
        sliding_window.push_back(price);
        updateMovingAverage();
        return;
    }
    double last_price = sliding_window.back();
    sliding_window.pop_front();
    sliding_window.push_back(price);
    updateMovingAverage();

    if(last_price < price && price > getMovingAverage()){
        Ob.createBuyOrder(quantity, price);
    } else if (last_price > price && price < getMovingAverage()){
        Ob.createSellOrder(quantity, price);
    }

    return;

}