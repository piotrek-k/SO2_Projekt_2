#ifndef SO2_PROJEKT_WORKER
#define SO2_PROJEKT_WORKER

#include "TableElement.h"

enum WorkerState
{
    HasNoJob,
    IsInDepot,
    DoesThermalProcessing,
    MakesSandwich
};

class Worker : public TableElement
{
private:
    WorkerState state = HasNoJob;

    void goToDepot();
    void processFood();
    void makeSandwich();

public:
    Worker(/* args */);
    ~Worker();

    std::string getName();
    std::string getStateName();

    void Simulate();
    void Kill();
};

#endif //SO2_PROJEKT_WORKER
