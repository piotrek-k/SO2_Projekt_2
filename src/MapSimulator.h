#ifndef SO2_PROJEKT_MAPSIMULATOR
#define SO2_PROJEKT_MAPSIMULATOR

#include <vector>
#include <queue>
#include "Deliveryman.h"
#include "Customer.h"
#include "Kitchen.h"

class MapSimulator
{
private:
    int sizeX = 0;
    int sizeY = 0;
    int kitchenLocX = 0;
    int kitchenLocY = 0;

    std::vector<Deliveryman *> allDeliverymans;
    std::vector<Customer *> allCustomers;
    Kitchen *kitchenRef;

    std::queue<Deliveryman *> waitingDeliverymans;
    std::queue<Customer *> waitingCustomers;

    void simulationThread();

public:
    MapSimulator(int sizeX, int sizeY, Kitchen* kitchen,
                 int numOfDeliverymans, int numOfClients, int clientOrderFrequency);
    ~MapSimulator();

    void StartSimulation();
    void Draw();
};

#endif //SO2_PROJEKT_MAPSIMULATOR