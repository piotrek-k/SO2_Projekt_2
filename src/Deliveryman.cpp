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
        std::unique_lock<std::mutex> ulock_dman(deliveryManager->deliverymanQueueMtx);
        deliveryManager->waitingDeliverymans.push(this);

        while(deliveryManager->waitingDeliverymans.front() != this){
            deliveryManager->deliverymanQueueCV.wait(ulock_dman);
        }

        while(deliveryManager->waitingOrdersToDeliver.size() == 0){
            deliveryManager->waitForOrdersCV.wait(ulock_dman);
        }

        // od tego miejsca gwarantowana jest obecność zamówienia w kolejce
        // dostawca ma wyłączność na jego odebranie

        orderInstance = deliveryManager->waitingOrdersToDeliver.front();
        targetCustomer = orderInstance->targetCustomerRef;
        deliveryManager->waitingOrdersToDeliver.pop();
        
        state = DeliveringOrder;

        deliveryManager->waitingDeliverymans.pop();
        deliveryManager->deliverymanQueueCV.notify_all();
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

            delete orderInstance;
            orderInstance = nullptr;
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

std::string Deliveryman::getName()
{
    return "Deliveryman";
}

std::string Deliveryman::getStateName()
{
    switch (state)
    {
    case DeliverymanState::WaitingForOrders:
        return "WaitingForOrders";
        break;
    case DeliverymanState::DeliveringOrder:
        return "DeliveringOrder";
        break;
    case DeliverymanState::ComingBackToKitchen:
        return "ComingBackToKitchen";
        break;

    default:
        break;
    }

    return "Unknown";
}

std::string Deliveryman::getOrderId()
{
    if (orderInstance != nullptr)
    {
        return "" + std::to_string(orderInstance->GetId());
    }
    return "Brak";
}