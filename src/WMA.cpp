#include "WMA.hpp"

WMA::WMA(int s){
    size = s;
    total_weight = (size * (size + 1))/2;
}

WMA::WMA(const WMA& rhs){
    sliding_window = rhs.getSlidingWindow();
    size = rhs.getSize();
    moving_average = rhs.getMovingAverage();
    total_weight = rhs.getTotalWeight();
}

WMA& WMA::operator=(const WMA& rhs){
    if(this != &rhs){
        sliding_window = rhs.getSlidingWindow();
        size = rhs.getSize();
        moving_average = rhs.getMovingAverage();
        total_weight = rhs.getTotalWeight();
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

int WMA::getTotalWeight() const {
    return total_weight;
}