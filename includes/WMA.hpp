//define a WMA strategy
#pragma once
#include "Strategy.hpp"
#include <queue>


class WMA : public Strategy {

private:
    deque<double> sliding_window;
    int size;
    double moving_average = 0;

public:
    WMA(int size);
    WMA(const WMA& rhs);
    WMA& operator=(const WMA& rhs);
    virtual ~WMA() = default;

    virtual void onMarketData(double price, int quantity, OrderBook& Ob) override;

    
    void updateMovingAverage();
    void setSize(int s);

    double getMovingAverage() const;
    int getSize() const;
    deque<double> getSlidingWindow() const;
};