#include "Deliveryman.h"

Deliveryman::Deliveryman(Kitchen *kitchenRef, std::vector<std::thread *> *globalThreadsContainerRef, DeliveryManager* deliveryManagerRef)
{
    kitchenInstance = kitchenRef;
    this->globalThreadsContainer = globalThreadsContainerRef;
    this->deliveryManager = deliveryManagerRef;
}

Deliveryman::~Deliveryman()
{
}

int Deliveryman::GetPositionX()
{
    return this->positionX;
}

int Deliveryman::GetPositionY()
{
    return this->positionY;
}

void Deliveryman::MainLoop()
{
    int currentTargetX = positionX;
    int currentTargetY = positionY;

    if (state == ComingBackToKitchen)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(DELIVERYMAN_STEP_TIME_MS));

        currentTargetX = std::get<0>(kitchenInstance->GetPositon());
        currentTargetY = std::get<1>(kitchenInstance->GetPositon());

        if (currentTargetY == positionY && currentTargetX == positionX)
        {
            state = WaitingForOrders;
        }
    }
    else if (state == WaitingForOrders)
    {
        if (deliveryManager->waitingOrders.size() == 0)
        {
            // wstrzymaj wątek
            std::unique_lock<std::mutex> ulock(deliveryManager->deliverymanQueueMtx);
            take_order_queue_CV.wait(ulock);
            // wątek wznawiany gdy DeliveryManager otrzyma nowy obiekt Order
            // oraz instancja Deliveryman jest pierwsza w kolejce oczekujących
        }

        if (deliveryManager->waitingOrders.size() > 0)
        {
            std::lock_guard<std::mutex> lock(deliveryManager->deliverymanQueueMtx);
            orderInstance = deliveryManager->waitingOrders.front();
            targetCustomer = orderInstance->targetCustomerRef;
            deliveryManager->waitingOrders.pop();
            
            state = DeliveringOrder;
        }
    }
    else if (state == DeliveringOrder)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(DELIVERYMAN_STEP_TIME_MS));

        currentTargetX = targetCustomer->GetPositionX();
        currentTargetY = targetCustomer->GetPositionY();

        if (currentTargetY == positionY && currentTargetX == positionX)
        {
            this->orderInstance->UnlockWaitingThreads();
            state = ComingBackToKitchen;
        }
    }

    if (positionX > currentTargetX)
    {
        positionX--;
    }

    if (positionX < currentTargetX)
    {
        positionX++;
    }

    if (positionY > currentTargetY)
    {
        positionY--;
    }

    if (positionY < currentTargetY)
    {
        positionY++;
    }
}

void Deliveryman::simulateThread(bool *stopSignal, Deliveryman *instance)
{
    bool ss = *stopSignal;
    while (!ss)
    {
        instance->MainLoop();
    }
}

void Deliveryman::StartSimulation(bool *stopSignal)
{
    std::thread *t = new std::thread(simulateThread, stopSignal, this);
    globalThreadsContainer->push_back(t);
}

// void Deliveryman::GiveOrder(Customer *customer, Order *order)
// {
//     targetCustomer = customer;
//     orderInstance = order;
// }