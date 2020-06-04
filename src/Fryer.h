#ifndef SO2_PROJEKT_FRYER
#define SO2_PROJEKT_FRYER

#include <mutex>
#include <functional>
#include "Worker.h"

enum FryerState
{
    Inactive,
    WorkingAndFoodNotYetPrepared,
    WorkingAndFoodBurnt
};
class Worker;

class Fryer
{
private:
    std::mutex mtx;
    bool taken = false;

public:
    Fryer();
    ~Fryer();

    bool TryToLockAndExecute(Worker *w, const std::function<void(Worker *)> &action);
    bool IsTaken() { return taken; }
};

#endif //SO2_PROJEKT_FRYER
