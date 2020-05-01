#ifndef SO2_PROJEKT_WORKER
#define SO2_PROJEKT_WORKER

enum WorkerState
{
    HasNoJob,
    IsInDepot,
    DoesThermalProcessing,
    MakesSandwich
};

class Worker
{
private:
    WorkerState state = HasNoJob;

    void goToDepot();
    void processFood();
    void makeSandwich();

public:
    Worker(/* args */);
    ~Worker();

    void Simulate();
    void Kill();
};

#endif //SO2_PROJEKT_WORKER
