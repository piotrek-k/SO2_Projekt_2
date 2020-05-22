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

const int DELIVERYMAN_STEP_TIME_MS = 100;

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

    std::vector<std::thread *> *globalThreadsContainer;

    static void simulateThread(bool *stopSignal, Deliveryman *instance);

public:
    Deliveryman(Kitchen* kitchenRef, std::vector<std::thread *> *globalThreadsContainerRef, DeliveryManager* deliveryManagerRef);
    ~Deliveryman();

    int GetPositionX();
    int GetPositionY();

    // void GiveOrder(Customer* customer, Order* order);

    void MainLoop();
    void StartSimulation(bool *stopSignal);
};


#endif //SO2_PROJEKT_DELIVERYMAN