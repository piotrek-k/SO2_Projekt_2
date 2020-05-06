#ifndef SO2_PROJEKT_MAPSIMULATOR
#define SO2_PROJEKT_MAPSIMULATOR

#include <vector>
#include <queue>
#include "Deliveryman.h"
#include "Customer.h"
#include "Kitchen.h"

class Customer;

class MapSimulator
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
    std::queue<Customer *> waitingCustomers;

    void simulationThread(bool *stopSignal);

public:
    MapSimulator(int sizeX, int sizeY, Kitchen *kitchen,
                 int numOfDeliverymans, int numOfClients, int clientOrderFrequency,
                 std::vector<std::thread *> *globalThreadsContainerRef);
    ~MapSimulator();

    void StartSimulation();
    void Draw();

    void NewOrder(Customer* orderer);
};

#endif //SO2_PROJEKT_MAPSIMULATOR