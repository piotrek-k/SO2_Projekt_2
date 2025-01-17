#include "KnivesManager.h"

KnivesManager::KnivesManager(int numOfKnives)
{
    this->numOfAvailableObjects = numOfKnives;
}

void KnivesManager::EnterQueue(Worker *w, const std::function<void(Worker *)> &action)
{
    {
        const std::lock_guard<std::mutex> lock(queueInsertMutex);
        workerQueue.push(w);
    }

    {
        std::unique_lock<std::mutex> unlock_object(queueMutex);

        while (workerQueue.front() != w || numOfAvailableObjects == 0)
        {
            cv.wait(unlock_object);
        }
        {
            const std::lock_guard<std::mutex> lock(counterMutex);
            numOfAvailableObjects--;
        }
        workerQueue.pop();
    }

    action(w);

    {
        const std::lock_guard<std::mutex> lock(counterMutex);
        numOfAvailableObjects++;
    }

    cv.notify_all();
}