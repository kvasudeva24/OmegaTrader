//define a EMA strategy
#pragma once
#include "Strategy.hpp"
#include <queue>


class EMA : public Strategy {

private:
    deque<double> sliding_window;
    int size;
    double moving_average = 0.0;
    static constexpr double k = 2.0;

public:
    EMA(int size);
    EMA(const EMA& rhs);
    EMA& operator=(const EMA& rhs);
    virtual ~EMA() = default;

    virtual void onMarketData(double price, int quantity, OrderBook& Ob) override;

    
    void updateMovingAverage();
    void setSize(int s);

    double getMovingAverage() const;
    int getSize() const;
    deque<double> getSlidingWindow() const;
    static double getK();
};