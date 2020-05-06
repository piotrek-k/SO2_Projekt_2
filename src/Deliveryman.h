#ifndef SO2_PROJEKT_DELIVERYMAN
#define SO2_PROJEKT_DELIVERYMAN

#include <thread>
#include <chrono>

#include "Customer.h"
#include "Order.h"
#include "DeliveryManager.h"

enum DeliverymanState {
    WaitingForOrders,
    DeliveringOrder,
    ComingBackToKitchen
};

const int DELIVERYMAN_STEP_TIME_MS = 1000;

class Customer;
class Order;
class Kitchen;
class DeliveryManager;

class Deliveryman
{
private:
    DeliverymanState state = ComingBackToKitchen;

    int positionX = 0;
    int positionY = 0;

    Customer* targetCustomer;
    Order* orderInstance;
    Kitchen* kitchenInstance;
    DeliveryManager* deliveryManager;

    void simulateThread(bool *stopSignal, Deliveryman *instance);

public:
    Deliveryman(Kitchen* kitchenRef);
    ~Deliveryman();

    int GetPositionX();
    int GetPositionY();

    // void GiveOrder(Customer* customer, Order* order);

    void MainLoop();

    std::condition_variable take_order_queue_CV;
};


#endif //SO2_PROJEKT_DELIVERYMAN