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
        std::map<char, int> prioritiesMap = {
            {'TakeOrder', kitchenInstance->GetWaitingOrdersNumber()},
            //{'GoToDepot', kitchenInstance->GetNumberOfOrdersToPrepare() - kitchenInstance->GetReadyIngredientsNumber()},
            {'ProcessFood', kitchenInstance->GetOrdersToHeat()},
            {'PrepareIngr', kitchenInstance->GetNumberOfOrdersToPrepare() - kitchenInstance->GetReadyIngredientsNumber()},
            {'MakeSandwich', kitchenInstance->GetNumberOfOrdersToPrepare()}};

        using pair_type = decltype(prioritiesMap)::value_type;

        auto maxElem = std::max_element(
            std::begin(prioritiesMap), std::end(prioritiesMap),
            [](const pair_type &p1, const pair_type &p2) {
                return p1.second < p2.second;
            });

        if (maxElem->first == 'TakeOrder')
        {
            state = TakingOrder;
        }
        else if (maxElem->second == 'GoToDepot')
        {
            state = IsInDepot;
        }
        else if (maxElem->first == 'ProcessFood')
        {
            state = DoesThermalProcessing;
        }
        else if (maxElem->first == 'PrepareIngr')
        {
            state = PrepareIngredient;
        }
        else if (maxElem->first == 'MakeSandwich')
        {
            state = MakesSandwich;
        }
    }
    else if (state == IsInDepot)
    {
    }
    else if (state == DoesThermalProcessing)
    {
    }
    else if (state == MakesSandwich)
    {
        Order *o = kitchenInstance->GetOrderToPrepare();
        if (this->kitchenInstance->TryGetReadyIngredients() &&
            o != nullptr)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(SANDWICH_PREPARATION_MS));
            kitchenInstance->PassOrderToHeat(o);
            state = HasNoJob;
        }
        else
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(PENALTY_MS));
            state = PrepareIngredient;
        }
    }
    else if (state == PrepareIngredient)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(INGREDIENTS_PREPARATION_MS));
        state = HasNoJob;
        kitchenInstance->AddNewReadyIngredient();
    }
    else if (state == TakingOrder)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ORDER_TAKING_MS));
        auto result = this->kitchenInstance->TryGetOrderToCarryOut();
        if (result != nullptr)
        {
            this->kitchenInstance->PassOrderToPrepare(result);
        }
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
    case WorkerState::IsInDepot:
        return "In depot";
        break;
    case WorkerState::MakesSandwich:
        return "Makes sandwich";
        break;
    case WorkerState::DoesThermalProcessing:
        return "Cooks";
        break;

    default:
        break;
    }

    return "Unknown";
}