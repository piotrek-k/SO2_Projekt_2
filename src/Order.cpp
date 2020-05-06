#include "Order.h"

Order::Order(Customer* customer){
    this->targetCustomerRef = customer;
}

Order::~Order(){
    
}

void Order::StartWaiting(){
    std::unique_lock<std::mutex> ulock(this->mtx);
    this->cv.wait(ulock);
}

void Order::UnlockWaitingThreads(){
    std::unique_lock<std::mutex> ulock(mtx);
    cv.notify_all();
}