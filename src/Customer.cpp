#include "Customer.h"

Customer::Customer(int orderFreq,
                   std::vector<std::thread *> *globalThreadsContainerRef,
                   MapSimulator *refToMap)
{
    this->orderFreq = orderFreq;
    this->globalThreadsContainer = globalThreadsContainerRef;
    this->mapRef = refToMap;
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

void Customer::simulationThread(bool *stopSignal, Customer* customer)
{
    customer->NextAction();
}

void Customer::MarkOrderAsCompleted()
{
    state = NoAction;
}

void Customer::NextAction()
{
    if (this->state == NoAction)
    {
        srand(time(NULL));
        float randomNum = (rand() % 10) / (float)10;
        int timeToNextOrder = (orderFreq + randomNum) * 1000;

        std::this_thread::sleep_for(std::chrono::milliseconds(timeToNextOrder));

        this->mapRef->NewOrder(this);
        state = WaitingForOrder;
    }
}