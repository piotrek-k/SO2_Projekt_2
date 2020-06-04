#ifndef SO2_PROJEKT_MAPSIMULATOR
#define SO2_PROJEKT_MAPSIMULATOR

#include <vector>
#include <queue>
#include <mutex>
#include "Deliveryman.h"
#include "Customer.h"
#include "Kitchen.h"
#include "Order.h"
#include "others/atomic_queue.h"

class Customer;
class Deliveryman;
class Kitchen;

class DeliveryManager
{
private:
    std::vector<Deliveryman *> allDeliverymans;
    std::vector<Customer *> allCustomers;
    Kitchen *kitchenRef;

    std::vector<std::thread *> *globalThreadsContainer = new std::vector<std::thread *>();

    void simulationThread(bool *stopSignal);

public:
    DeliveryManager(int sizeX, int sizeY, Kitchen *kitchen,
                    int numOfDeliverymans, int numOfClients, int clientOrderFrequency,
                    std::vector<std::thread *> *globalThreadsContainerRef);
    ~DeliveryManager();

    void StartSimulation();
    void Draw();

    void NewOrderToCarryOut(Order *o);
    void OrderReadyToDeliver(Order *o);

    std::vector<Deliveryman *> GetDeliverymans() { return allDeliverymans; }

    atomic_queue<Deliveryman *> waitingDeliverymans;
    atomic_queue<Order *> waitingOrdersToDeliver;

    std::mutex deliverymanQueueMtx;
    std::condition_variable deliverymanQueueCV;
    std::condition_variable waitForOrdersCV;

    int orderCounter = 0;
    std::mutex orderCounterMtx;

    int positionX = 0;
    int positionY = 0;
    int sizeX = 0;
    int sizeY = 0;
};

#endif //SO2_PROJEKT_MAPSIMULATOR