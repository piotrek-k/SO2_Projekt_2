#ifndef SO2_PROJEKT_WORKER
#define SO2_PROJEKT_WORKER

#include "TableElement.h"
#include "Kitchen.h"
#include <map>
#include <thread>
#include <algorithm>
#include "Globals.h"

class Kitchen;

enum WorkerState
{
    HasNoJob,
    IsInDepot,
    DoesThermalProcessing,
    MakesSandwich,
    PrepareIngredient,
    TakingOrder
};

class Worker : public TableElement
{
private:
    WorkerState state = HasNoJob;

    Kitchen* kitchenInstance;

    void goToDepot();
    void processFood();
    void makeSandwich();

    std::vector<std::thread *> *globalThreadsContainer;

    static void simulateThread(bool *stopSignal, Worker *instance);

public:
    Worker(Kitchen* kitchenRef, std::vector<std::thread *> *globalThreadsContainerRef);
    ~Worker();

    std::string getName();
    std::string getStateName();

    void StartSimulation(bool *stopSignal);
    void Kill();

    void MainLoop();
};

#endif //SO2_PROJEKT_WORKER
