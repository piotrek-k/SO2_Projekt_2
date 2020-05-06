#ifndef SO2_PROJEKT_ORDER
#define SO2_PROJEKT_ORDER

#include <mutex>
#include <condition_variable>
#include "Customer.h"

class Customer;

class Order
{
private:
public:
    Order(Customer* customer);
    ~Order();

    std::mutex mtx;
    std::condition_variable cv;

    Customer *targetCustomerRef;

    void StartWaiting();
    void UnlockWaitingThreads();
};

#endif //SO2_PROJEKT_ORDER