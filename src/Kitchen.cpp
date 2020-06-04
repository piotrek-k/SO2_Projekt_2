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

    for (int f = 0; f < 2; f++)
    {
        fryers.push_back(new Fryer());
    }

    mainTable = new Table(55, 1, std::vector<int>{1, 1, 1}, 55);
    orderQueuesTable = new Table(115, 1, std::vector<int>{1, 3}, 50);

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
    std::vector<std::string> mainTableColumnNames;

    mainTableColumnNames.push_back("Typ");
    mainTableColumnNames.push_back("Czynnosc");
    mainTableColumnNames.push_back("Id zamowienia");

    for (auto &w : workers)
    {
        std::vector<std::string> row;
        row.push_back(w->getName());
        row.push_back(w->getStateName());
        row.push_back(w->getOrderId());
        mainTableContents.push_back(row);
    }

    for (auto &w : deliveryManager->GetDeliverymans())
    {
        std::vector<std::string> row;
        row.push_back(w->getName());
        row.push_back(w->getStateName());
        row.push_back(w->getOrderId());
        mainTableContents.push_back(row);
    }

    mainTable->generateTable(mainTableColumnNames, mainTableContents);

    std::vector<std::vector<std::string>> ordersQueueContents;
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Oczekujace nowe zamowienia",
                std::to_string(GetWaitingOrdersNumber())});
    }
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Zamowenia do dostarczenia",
                std::to_string(deliveryManager->waitingOrdersToDeliver.size())});
    }
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Dostawcy bez pracy",
                std::to_string(deliveryManager->waitingDeliverymans.size())});
    }
    {
        ordersQueueContents.push_back(
            std::vector<std::string>{
                "Nieuzywane smazalnice",
                std::to_string(GetNumberOfUnusedFryers()) + "/" +
                    std::to_string(fryers.size())});
    }
    orderQueuesTable->generateTable(std::vector<std::string>{"Nazwa zasobu", "Wartosc"}, ordersQueueContents);
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

int Kitchen::GetNumberOfUnusedFryers()
{
    int counter = 0;
    for (auto &f : fryers)
    {
        if (f->IsTaken())
        {
            counter++;
        }
    }

    return counter;
}