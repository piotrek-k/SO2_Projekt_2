#include <curses.h>
#include <thread>

#include "DeliveryManager.h"
#include "Globals.h"

DeliveryManager::DeliveryManager(int sizeX, int sizeY, Kitchen *kitchen,
                                 int numOfDeliverymans, int numOfClients, int clientOrderFrequency,
                                 std::vector<std::thread *> *globalThreadsContainerRef)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->kitchenRef = kitchen;

    this->globalThreadsContainer = globalThreadsContainerRef;

    srand(time(NULL));

    for (int d = 0; d < numOfDeliverymans; d++)
    {
        allDeliverymans.push_back(new Deliveryman(kitchen, globalThreadsContainer, this));
    }

    for (int d = 0; d < numOfClients; d++)
    {
        allCustomers.push_back(new Customer(clientOrderFrequency, globalThreadsContainer, this));
    }
}

DeliveryManager::~DeliveryManager()
{
}

void DeliveryManager::StartSimulation()
{
    bool stopSignal = false;
    // std::thread *t = new std::thread(simulationThread, &stopSignal);
    // globalThreadsContainer->push_back(t);

    for (auto &c : allCustomers)
    {
        c->StartSimulation(&stopSignal);
    }

    for (auto &d : allDeliverymans)
    {
        d->StartSimulation(&stopSignal);
    }
}

void DeliveryManager::Draw()
{
    for (int x = 0; x < this->sizeX; x++)
    {
        for (int y = 0; y < this->sizeY; y++)
        {
            attron(COLOR_PAIR(MAP_BACKGROUND));
            mvaddch(this->positionY + y, this->positionX + x, ' ');
            attroff(COLOR_PAIR(MAP_BACKGROUND));
        }
    }

    for (auto &d : allDeliverymans)
    {
        attron(COLOR_PAIR(MAP_DELIVERYMAN));
        mvaddch(this->positionY + d->GetPositionY(),
                this->positionX + d->GetPositionX(), '*');
        attroff(COLOR_PAIR(MAP_DELIVERYMAN));
    }

    for (auto &c : allCustomers)
    {
        int color = c->GetState() == WaitingForOrder ? MAP_CLIENT_ACTIVE : MAP_CLIENT;
        attron(COLOR_PAIR(color));
        mvaddch(this->positionY + c->GetPositionY(),
                this->positionX + c->GetPositionX(), ' ');
        attroff(COLOR_PAIR(color));
    }

    attron(COLOR_PAIR(MAP_KITCHEN));
    mvaddch(this->positionY + std::get<0>(this->kitchenRef->GetPositon()),
            this->positionX + std::get<1>(this->kitchenRef->GetPositon()), ' ');
    attroff(COLOR_PAIR(MAP_KITCHEN));
}

void DeliveryManager::simulationThread(bool *stopSignal)
{
    while (!stopSignal)
    {
    }
}

void DeliveryManager::NewOrder(Order *o)
{
    this->waitingOrders.push(o);

    deliverymanQueueCV.notify_all();
    waitForOrdersCV.notify_all();
}