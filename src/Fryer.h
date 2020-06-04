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
    // void simulate();
    std::mutex mtx;
public:
    Fryer(/* args */);
    ~Fryer();

    bool TryToLockAndExecute(Worker *w, const std::function<void(Worker*)>& action);
};

#endif //SO2_PROJEKT_FRYER
