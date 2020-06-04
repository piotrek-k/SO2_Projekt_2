#include "Fryer.h"
#include <mutex>
#include <functional>
#include "Worker.h"

Fryer::Fryer(){
    
}

bool Fryer::TryToLockAndExecute(Worker *w, const std::function<void(Worker*)>& action)
{
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
    if (!lock.owns_lock())
    {
        // mutex wasn't locked. Handle it.
        return false;
    }
    
    taken = true;

    action(w);

    taken = false;

    return true;
}