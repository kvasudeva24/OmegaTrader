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
            while(!ask_book.empty() && order.getQuantity() > 0 && order.getPrice() > ask_book.begin()->first){
                //get the best ask inside the loop to avoid overriting
                Order& best_ask = getBestAsk();

                //fill the order as much as poss
                order.setQuantity(order.getQuantity() - best_ask.getQuantity());

                //if the price we filled at is the only one erase it so we can deref prop
                if(ask_book.begin()->second.size() == 1){
                    ask_book.begin()->second.pop(); //queue space will be reclaimed but safe practice
                    ask_book.erase(ask_book.begin()->first);
                } else {
                    //pop from queue
                    ask_book.begin()->second.pop();
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
    if(bid_book.find(order.getPrice()) == bid_book.end()){
        queue<Order> q; q.push(order);
        bid_book[order.getPrice()] = q;
    } else {
        bid_book[order.getPrice()].push(order);
    }
}