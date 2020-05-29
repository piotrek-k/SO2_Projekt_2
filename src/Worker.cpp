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
    }
    else if (state == IsInDepot)
    {
    }
    else if (state == DoesThermalProcessing)
    {
    }
    else if (state == MakesSandwich)
    {
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