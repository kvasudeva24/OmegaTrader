//define a SMA strategy
#include <Strategy.hpp>
#include <queue>


class SMA : public Strategy {

private:
    deque<double> sliding_window;
    int size;
    double moving_average;

public:
    SMA(int size);
    SMA(const SMA& rhs);
    SMA& operator=(const SMA& rhs);
    virtual ~SMA() = default;

    virtual void onMarketData(double price, int quantity, OrderBook& Ob) override;

    double getMovingAverage() const;
    void updateMovingAverage();

    int getSize() const;
    void setSize(int s);
};