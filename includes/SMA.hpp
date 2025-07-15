//define a SMA strategy
#pragma once
#include <Strategy.hpp>
#include <queue>


class SMA : public Strategy {

private:
    deque<double> sliding_window;
    int size;
    double moving_average = 0;

public:
    SMA(int size);
    SMA(const SMA& rhs);
    SMA& operator=(const SMA& rhs);
    virtual ~SMA() = default;

    virtual void onMarketData(double price, int quantity, OrderBook& Ob) override;

    
    void updateMovingAverage();
    void setSize(int s);

    double getMovingAverage() const;
    int getSize() const;
    deque<double> getSlidingWindow() const;
};