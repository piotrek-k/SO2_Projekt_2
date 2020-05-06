#ifndef SO2_PROJEKT_CUSTOMER
#define SO2_PROJEKT_CUSTOMER

#include <thread>
#include <vector>
#include "MapSimulator.h"

enum CustomerState {
    NoAction,
    WaitingForOrder
};

class MapSimulator;

class Customer
{
private:
    CustomerState state = NoAction;

    std::vector<std::thread *> *globalThreadsContainer;
    MapSimulator* mapRef;

    int locationX = 0;
    int locationY = 0;
    int orderFreq = 0;

    int waitingTime = 0;

    void makeOrder();
    static void simulationThread(bool *stopSignal, Customer* customer);

public:
    Customer(int orderFreq,
            std::vector<std::thread *> *globalThreadsContainerRef,
            MapSimulator* refToMap);
    ~Customer();

    int GetPositionX();
    int GetPositionY();

    void StartSimulation(bool* stopSignal);
    void MarkOrderAsCompleted();

    void NextAction();
};

#endif //SO2_PROJEKT_CUSTOMER