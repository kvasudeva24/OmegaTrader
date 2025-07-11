#include "OrderBook.hpp"

#include <stdexcept>
#include <iostream>
#include <memory>

void OrderBook::createBuyOrder(int q, double p){
    //first create the order ptr
    unique_ptr<Order> ptr = make_unique<Order>(next_id_counter++, q, p, Side::BUY);

    //if the ask book isnt empty then we can check if the
    //order crosses the line 
    if(!ask_book.empty()){
        //because you can move ptr once it is valid with if/else
        checkAskBook(std::move(ptr));
    } else {
        insertBuyOrder(std::move(ptr));
    }
}

void OrderBook::checkAskBook(unique_ptr<Order> ptr){

    //check if crosses
    if(ptr->getPrice() >= ask_book.begin()->first){
        //CASE 1: best ask q > order q
        if(getBestAsk().getQuantity() > ptr->getQuantity()){
            getBestAsk().setQuantity(getBestAsk().getQuantity() - ptr->getQuantity());
        } else {
            // CASE 2: order q > best ask q --> need to fullfill as much as possible
            //while the map isnt empty, order has q, and it crosses the line
            while(!ask_book.empty() && ptr->getQuantity() > 0 && ptr->getPrice() >= ask_book.begin()->first){
                //get the best ask inside the loop to avoid overriting
                Order& best_ask = getBestAsk();

                //fill the order as much as poss
                ptr->setQuantity(ptr->getQuantity() - best_ask.getQuantity());

                //if the price we filled at is the only one erase it so we can deref prop
                if(ask_book.begin()->second.size() == 1){
                    ask_book.begin()->second.pop_front(); //queue space will be reclaimed but safe practice
                    ask_book.erase(ask_book.begin()->first);
                } else {
                    //pop from queue
                    ask_book.begin()->second.pop_front();
                }  
            }

            //if the order was fully matched we are good if not insert 
            if(ptr->getQuantity() > 0){
                insertBuyOrder(std::move(ptr));
            }

        }
    } else {
        //it doesnt cross, add order
        insertBuyOrder(std::move(ptr));
    }
}

Order& OrderBook::getBestAsk(){
    if(ask_book.empty()) throw out_of_range("Book is empty");
    return *(ask_book.begin()->second.front());
}

void OrderBook::insertBuyOrder(unique_ptr<Order> ptr){
    int id = ptr->getID();
    double price = ptr->getPrice();
    Side side = ptr->getSide();

    auto& order_list = bid_book[price];
    auto it = order_list.insert(order_list.end(), std::move(ptr));
    id_map[id] = {price, side, it};
}

void OrderBook::createSellOrder(int q, double p){
    //first create the order ptr
    unique_ptr<Order> ptr = make_unique<Order>(next_id_counter++, q, p, Side::SELL);

    //if the bid book isnt empty then we can check if the
    //order crosses the line 
    if(!bid_book.empty()){
        checkBidBook(std::move(ptr));
    } else {
        insertSellOrder(std::move(ptr));
    }
}


void OrderBook::checkBidBook(unique_ptr<Order> ptr){

    //check if crosses
    if(ptr->getPrice() <= bid_book.begin()->first){
        //CASE 1: best bid q > order q
        if(getBestBid().getQuantity() > ptr->getQuantity()){
            getBestBid().setQuantity(getBestBid().getQuantity() - ptr->getQuantity());
        } else {
            // CASE 2: order q > best bid q --> need to fullfill as much as possible
            //while the map isnt empty, order has q, and it crosses the line
            while(!bid_book.empty() && ptr->getQuantity() > 0 && ptr->getPrice() <= bid_book.begin()->first){
                //get the best bid inside the loop to avoid overriting
                Order& best_bid = getBestBid();

                //fill the order as much as poss
                ptr->setQuantity(ptr->getQuantity() - best_bid.getQuantity());

                //if the price we filled at is the only one erase it so we can deref prop
                if(bid_book.begin()->second.size() == 1){
                    bid_book.begin()->second.pop_front(); //list space will be reclaimed but safe practice
                    bid_book.erase(bid_book.begin()->first);
                } else {
                    //pop from queue
                    bid_book.begin()->second.pop_front();
                }  
            }

            //if the order was fully matched we are good if not insert 
            if(ptr->getQuantity() > 0){
                insertSellOrder(std::move(ptr));
            }

        }
    } else {
        //it doesnt cross, add order
        insertSellOrder(std::move(ptr));
    }
}

Order& OrderBook::getBestBid(){
    if(bid_book.empty()) throw out_of_range("Book is empty");
    return *(bid_book.begin()->second.front());
}

void OrderBook::insertSellOrder(unique_ptr<Order> ptr){
    int id = ptr->getID();
    double price = ptr->getPrice();
    Side side = ptr->getSide();

    auto& order_list = ask_book[price];
    auto it = order_list.insert(order_list.end(), std::move(ptr));
    id_map[id] = {price, side, it};
}

void OrderBook::cancelOrder(int id){
    if(id_map.find(id) == id_map.end()) throw invalid_argument("Id does not exist");

    auto [price, side, it] = id_map[id];
    if(side == Side::BUY){
        auto& list = bid_book[price];
        list.erase(it);
        if(list.empty()) bid_book.erase(price);
    } else {
        auto& list = ask_book[price];
        list.erase(it);
        if(list.empty()) ask_book.erase(price);
    }
    id_map.erase(id);
}

void OrderBook::printBidBook(){
    if(bid_book.empty()){
        cout << "Bid book is empty;" << endl;
        return;
    } 

    for(const auto& [price, list] : bid_book){
        for(const auto& ptr : list){
            cout << ptr->toString() << endl;
        }
    }
}

void OrderBook::printAskBook(){
    if(ask_book.empty()){
        cout << "Ask book is empty;" << endl;
        return;
    }

    for(const auto& [price, list] : ask_book){
        for(const auto& ptr : list){
            cout << ptr->toString() << endl;
        }
    }
}