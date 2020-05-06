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
    std::vector<Deliveryman *> allDeliverymans;
    std::vector<Customer *> allCustomers;
    Kitchen *kitchenRef;

    std::vector<std::thread *> *globalThreadsContainer = new std::vector<std::thread *>();

    std::queue<Deliveryman *> waitingDeliverymans = std::queue<Deliveryman *>();

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

    int positionX = 0;
    int positionY = 0;
    int sizeX = 0;
    int sizeY = 0;
};

#endif //SO2_PROJEKT_MAPSIMULATOR