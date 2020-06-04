#include "KnivesManager.h"

KnivesManager::KnivesManager(int numOfKnives)
{
    this->numOfAvailableObjects = numOfKnives;
}

void KnivesManager::EnterQueue(Worker *w)
{
    {
        const std::lock_guard<std::mutex> lock(queueInsertMutex);
        workerQueue.push(w);
    }

    std::unique_lock<std::mutex> unlock_object(queueMutex);
    while (workerQueue.front() != w)
    {
        cv.wait(unlock_object);
    }
    workerQueue.pop();

    {
        const std::lock_guard<std::mutex> lock(counterMutex);
        if (numOfAvailableObjects > 1)
        {
            numOfAvailableObjects--;
            cv.notify_all();
        }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SANDWICH_PREPARATION_MS));

    {
        const std::lock_guard<std::mutex> lock(counterMutex);
        numOfAvailableObjects++;
    }

    cv.notify_all();
}