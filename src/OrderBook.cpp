#include "OrderBook.hpp"

void OrderBook::createBuyOrder(int q, double p){
    //first create the order 
    Order order = {next_id_counter++, q, p, Side::BUY};

    //if the ask book isnt empty then we can check if the
    //order crosses the line 
    if(!ask_book.empty()){
        checkAskBook(order);
    } else {
        insertBuyOrder(order);
    }
}

void OrderBook::checkAskBook(Order& order){
    Order& curr_best = getBestAsk();

    //check if crosses
    if(order.getPrice() >= ask_book.begin()->first){
        //CASE 1: best ask q > order q
        if(curr_best.getQuantity() > order.getQuantity()){
            curr_best.setQuantity(curr_best.getQuantity() - order.getQuantity());
        } else {
            // CASE 2: order q > best ask q --> need to fullfill as much as possible
            //while the map isnt empty, order has q, and it crosses the line
            while(!ask_book.empty() && order.getQuantity() > 0 && order.getPrice() >= ask_book.begin()->first){
                //get the best ask inside the loop to avoid overriting
                Order& best_ask = getBestAsk();

                //fill the order as much as poss
                order.setQuantity(order.getQuantity() - best_ask.getQuantity());

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
            if(order.getQuantity() > 0){
                insertBuyOrder(order);
            }

        }
    } else {
        //it doesnt cross, add order
        insertBuyOrder(order);
    }
}

Order& OrderBook::getBestAsk(){
    return ask_book.begin()->second.front();
}

void OrderBook::insertBuyOrder(Order& order){
    auto& order_list = bid_book[order.getPrice()];
    auto it = order_list.insert(order_list.end(), order);
    id_map[order.getID()] = {order.getPrice(), order.getSide(), it};
}

void OrderBook::createSellOrder(int q, double p){
    //first create the order 
    Order order = {next_id_counter++, q, p, Side::SELL};

    //if the bid book isnt empty then we can check if the
    //order crosses the line 
    if(!bid_book.empty()){
        checkBidBook(order);
    } else {
        insertSellOrder(order);
    }
}


void OrderBook::checkBidBook(Order& order){
    Order& curr_best = getBestBid();

    //check if crosses
    if(order.getPrice() <= bid_book.begin()->first){
        //CASE 1: best bid q > order q
        if(curr_best.getQuantity() > order.getQuantity()){
            curr_best.setQuantity(curr_best.getQuantity() - order.getQuantity());
        } else {
            // CASE 2: order q > best bid q --> need to fullfill as much as possible
            //while the map isnt empty, order has q, and it crosses the line
            while(!bid_book.empty() && order.getQuantity() > 0 && order.getPrice() <= bid_book.begin()->first){
                //get the best bid inside the loop to avoid overriting
                Order& best_bid = getBestBid();

                //fill the order as much as poss
                order.setQuantity(order.getQuantity() - best_bid.getQuantity());

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
            if(order.getQuantity() > 0){
                insertSellOrder(order);
            }

        }
    } else {
        //it doesnt cross, add order
        insertSellOrder(order);
    }
}

Order& OrderBook::getBestBid(){
    return bid_book.begin()->second.front();
}

void OrderBook::insertSellOrder(Order& order){
    auto& order_list = ask_book[order.getPrice()];
    auto it = order_list.insert(order_list.end(), order);
    id_map[order.getID()] = {order.getPrice(), order.getSide(), it};
}