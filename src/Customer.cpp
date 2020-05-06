#include "Customer.h"

Customer::Customer(int orderFreq,
                   std::vector<std::thread *> *globalThreadsContainerRef,
                   DeliveryManager *refToMap)
{
    this->orderFreq = orderFreq;
    this->globalThreadsContainer = globalThreadsContainerRef;
    this->mapRef = refToMap;

    this->locationX = (rand() % this->mapRef->sizeX);
    this->locationY = (rand() % this->mapRef->sizeY);
}

int Customer::GetPositionX()
{
    return this->locationX;
}

int Customer::GetPositionY()
{
    return this->locationY;
}

void Customer::StartSimulation(bool *stopSignal)
{
    std::thread *t = new std::thread(simulationThread, stopSignal, this);
    globalThreadsContainer->push_back(t);
}

void Customer::simulationThread(bool *stopSignal, Customer *customer)
{
    while (!*stopSignal)
    {
        customer->MainLoop();
    }
}

void Customer::MarkOrderAsCompleted()
{
    state = NoAction;
}

void Customer::MainLoop()
{
    srand(time(NULL));
    float randomNum = (rand() % 10) / (float)10;
    int timeToNextOrder = (orderFreq + randomNum) * 1000;

    std::this_thread::sleep_for(std::chrono::milliseconds(timeToNextOrder));

    activeOrder = new Order(this);

    this->mapRef->NewOrder(activeOrder);
    state = WaitingForOrder;

    activeOrder->StartWaiting();
    state = NoAction;
}