#include "Kitchen.h"

#include <curses.h>

Kitchen::Kitchen(int positionX, int positionY, int numOfWorkers, int numOfKnives)
{
    this->positionX = positionX;
    this->positionY = positionY;

    for (int w = 0; w < numOfWorkers; w++)
    {
        workers.push_back(new Worker(this, globalThreadsContainer));
    }

    for(int f = 0; f < 2; f++){
        fryers.push_back(new Fryer());
    }

    mainTable = new Table(55, 1, std::vector<int>{1, 1, 1}, 50);
    orderQueuesTable = new Table(55, 15, std::vector<int>{1, 3}, 50);

    knivesManager = new KnivesManager(numOfKnives);
}

void Kitchen::StartSimulation()
{
    bool stopSignal = false;

    for (auto &w : workers)
    {
        w->StartSimulation(&stopSignal);
    }
}

void Kitchen::Draw()
{
    std::vector<std::vector<std::string>> mainTableContents;

    for (auto &w : workers)
    {
        std::vector<std::string> row;
        row.push_back(w->getName());
        row.push_back(w->getStateName());
        row.push_back(w->getOrderId());
        mainTableContents.push_back(row);
    }

    mainTable->generateTable(mainTableContents);

    std::vector<std::vector<std::string>> ordersQueueContents;
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Oczekujace zamowienia",
                std::to_string(GetWaitingOrdersNumber())});
    }
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Skladane kanapki",
                std::to_string(GetNumberOfOrdersToPrepare())});
    }
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Podgrzewane skladniki",
                std::to_string(GetOrdersToHeat())});
    }
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Oczekujace skladniki",
                std::to_string(GetReadyIngredientsNumber())});
    }
    orderQueuesTable->generateTable(ordersQueueContents);
}

void Kitchen::PassNewOrder(Order *o)
{
    this->waitingOrders.push(o);
}

void Kitchen::simulationThread()
{
}

Order *Kitchen::TryGetOrderToCarryOut()
{
    std::unique_lock<std::mutex> lock(ordersMutex, std::try_to_lock);
    if (lock.owns_lock())
    {
        if (waitingOrders.size() > 0)
        {
            //waitingOrders--;
            Order *temp = waitingOrders.front();
            waitingOrders.pop();
            return temp;
        }
    }
    return nullptr;
}

bool Kitchen::TryGetReadyIngredients()
{
    std::unique_lock<std::mutex> lock(readyIngredientsMutex, std::try_to_lock);
    if (lock.owns_lock())
    {
        if (waitingReadyIngredients > 0)
        {
            waitingReadyIngredients--;
            return true;
        }
    }
    return false;
}

void Kitchen::AddNewReadyIngredient()
{
    waitingReadyIngredients++;
}