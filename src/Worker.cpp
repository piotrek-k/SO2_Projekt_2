#include "Worker.h"

Worker::Worker(Kitchen *kitchenRef, std::vector<std::thread *> *globalThreadsContainerRef)
{
    kitchenInstance = kitchenRef;
    this->globalThreadsContainer = globalThreadsContainerRef;
}

Worker::~Worker()
{
}

std::string Worker::getName()
{
    return "Worker";
}

void Worker::MainLoop()
{
    if (state == HasNoJob)
    {
        // Getting Order
        Order *resultOrder = kitchenInstance->GetOrderToPrepare();
        while (resultOrder == nullptr)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            resultOrder = kitchenInstance->GetOrderToPrepare();
        }
        order = resultOrder;

        state = WaitsForKnife;
        kitchenInstance->knivesManager->EnterQueue(this, [](Worker *w) {
            w->setState(WorkerState::PreparesFood);
            std::this_thread::sleep_for(std::chrono::milliseconds(SANDWICH_PREPARATION_MS));
        });
        state = FinishedPreparation;
    }
    else if (state == FinishedPreparation)
    {
        state = WaitsForFryer;

        bool fryingFinished = false;
        while (!fryingFinished)
        {
            for (auto &f : kitchenInstance->fryers)
            {
                fryingFinished = f->TryToLockAndExecute(this, [](Worker *w) {
                    w->setState(WorkerState::FriesFood);
                    std::this_thread::sleep_for(std::chrono::milliseconds(FRYING_TIME_MS));
                });

                if (fryingFinished)
                {
                    break;
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(PENALTY_MS));
        }

        state = FinalFoodPreparation;
    }
    else if (state == FinalFoodPreparation)
    {
        kitchenInstance->deliveryManager->OrderReadyToDeliver(order);
        order = nullptr;
        state = HasNoJob;
    }
}

void Worker::StartSimulation(bool *stopSignal)
{
    std::thread *t = new std::thread(simulateThread, stopSignal, this);
    globalThreadsContainer->push_back(t);
}

void Worker::simulateThread(bool *stopSignal, Worker *instance)
{
    bool ss = *stopSignal;
    while (!ss)
    {
        instance->MainLoop();
    }
}

std::string Worker::getStateName()
{
    switch (state)
    {
    case WorkerState::HasNoJob:
        return "No job";
        break;
    case WorkerState::WaitsForKnife:
        return "WaitsForKnife";
        break;
    case WorkerState::PreparesFood:
        return "PreparesFood";
        break;
    case WorkerState::WaitsForFryer:
        return "WaitsForFryer";
        break;
    case WorkerState::FriesFood:
        return "FriesFood";
        break;
    case WorkerState::FinalFoodPreparation:
        return "FinalFoodPreparation";
        break;

    default:
        break;
    }

    return "Unknown";
}

std::string Worker::getOrderId()
{
    if (order != nullptr)
    {
        return "" + std::to_string(order->GetId());
    }
    return "Undefined";
}