#include "Cabinet.h"
#include <mutex>

Cabinet::Cabinet(/* args */)
{
}

Cabinet::~Cabinet()
{
}

bool Cabinet::TryGetFood()
{
    std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);
    if (lock.owns_lock())
    {
        if (ingredientSets > 0)
        {
            ingredientSets--;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}