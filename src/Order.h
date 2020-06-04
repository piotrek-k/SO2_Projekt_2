#ifndef SO2_PROJEKT_ORDER
#define SO2_PROJEKT_ORDER

#include <mutex>
#include <condition_variable>
#include "Customer.h"

class Customer;

class Order
{
private:
    int id = 0;

public:
    Order(Customer *customer, int counter);
    ~Order();

    std::mutex mtx;
    std::condition_variable cv;

    Customer *targetCustomerRef;

    void StartWaiting();
    void UnlockWaitingThreads();
    int GetId() { return id; }
};

#endif //SO2_PROJEKT_ORDER