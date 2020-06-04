#ifndef SO2_PROJEKT_KNIFE
#define SO2_PROJEKT_KNIFE

#include <mutex>
#include <queue>
#include <condition_variable>
#include "Worker.h"

class Worker;

class KnivesManager
{
private:
    std::mutex queueInsertMutex;
    std::mutex queueMutex;
    std::mutex counterMutex;
    std::condition_variable cv;

    std::queue<Worker *> workerQueue;

    int numOfAvailableObjects = 0;

public:
    KnivesManager(int numOfKnives);
    ~KnivesManager();

    void EnterQueue(Worker *w);
};

#endif //SO2_PROJEKT_KNIFE