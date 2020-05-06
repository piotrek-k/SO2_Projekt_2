#ifndef SO2_PROJEKT_MAPSIMULATOR
#define SO2_PROJEKT_MAPSIMULATOR

#include <vector>
#include <queue>
#include "Deliveryman.h"
#include "Customer.h"
#include "Kitchen.h"
#include "Order.h"

class Customer;
class Deliveryman;

class DeliveryManager
{
private:
    const int positionX = 0;
    const int positionY = 0;
    int sizeX = 0;
    int sizeY = 0;
    int kitchenLocX = 0;
    int kitchenLocY = 0;

    std::vector<Deliveryman *> allDeliverymans;
    std::vector<Customer *> allCustomers;
    Kitchen *kitchenRef;

    std::vector<std::thread *> *globalThreadsContainer;

    std::queue<Deliveryman *> waitingDeliverymans;

    void simulationThread(bool *stopSignal);

public:
    DeliveryManager(int sizeX, int sizeY, Kitchen *kitchen,
                    int numOfDeliverymans, int numOfClients, int clientOrderFrequency,
                    std::vector<std::thread *> *globalThreadsContainerRef);
    ~DeliveryManager();

    void StartSimulation();
    void Draw();

    void NewOrder(Order *o);

    std::queue<Order *> waitingOrders;
    std::mutex deliverymanQueueMtx;
};

#endif //SO2_PROJEKT_MAPSIMULATOR