#include <curses.h>
#include <thread>

#include "MapSimulator.h"
#include "Globals.h"

MapSimulator::MapSimulator(int sizeX, int sizeY, Kitchen *kitchen,
                           int numOfDeliverymans, int numOfClients, int clientOrderFrequency,
                           std::vector<std::thread *> *globalThreadsContainerRef)
{
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->kitchenRef = kitchen;

    this->globalThreadsContainer = globalThreadsContainerRef;

    for (int d = 0; d < numOfDeliverymans; d++)
    {
        allDeliverymans.push_back(new Deliveryman());
    }

    for (int d = 0; d < numOfClients; d++)
    {
        allCustomers.push_back(new Customer(clientOrderFrequency, globalThreadsContainer, this));
    }
}

MapSimulator::~MapSimulator()
{
}

void MapSimulator::StartSimulation()
{
    bool stopSignal = false;
    // std::thread *t = new std::thread(simulationThread, &stopSignal);
    // globalThreadsContainer->push_back(t);

    for (auto &c : allCustomers)
    {
        c->StartSimulation(&stopSignal);
    }
}

void MapSimulator::Draw()
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
        attron(COLOR_PAIR(MAP_CLIENT));
        mvaddch(this->positionY + c->GetPositionY(),
            this->positionX + c->GetPositionX(), ' ');
        attroff(COLOR_PAIR(MAP_CLIENT));
    }
}

void MapSimulator::simulationThread(bool *stopSignal)
{
    while(!stopSignal){

    }
}

void MapSimulator::NewOrder(Customer* orderer){
    this->waitingCustomers.push(orderer);
}