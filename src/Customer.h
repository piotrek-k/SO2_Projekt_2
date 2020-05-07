#ifndef SO2_PROJEKT_CUSTOMER
#define SO2_PROJEKT_CUSTOMER

#include <thread>
#include <vector>
#include "DeliveryManager.h"
#include "Order.h"

enum CustomerState {
    NoAction,
    WaitingForOrder
};

class DeliveryManager;
class Order;

class Customer
{
private:
    CustomerState state = NoAction;

    std::vector<std::thread *> *globalThreadsContainer;
    DeliveryManager* mapRef;

    int locationX = 0;
    int locationY = 0;
    int orderFreq = 0;

    int waitingTime = 0;

    Order* activeOrder;

    void makeOrder();
    static void simulationThread(bool *stopSignal, Customer* customer);

public:
    Customer(int orderFreq,
            std::vector<std::thread *> *globalThreadsContainerRef,
            DeliveryManager* refToMap);
    ~Customer();

    int GetPositionX();
    int GetPositionY();

    void StartSimulation(bool* stopSignal);
    void MarkOrderAsCompleted();
    CustomerState GetState();

    void MainLoop();
};

#endif //SO2_PROJEKT_CUSTOMER