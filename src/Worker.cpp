#include "Worker.h"

Worker::Worker(/* args */)
{
}

Worker::~Worker()
{
}

std::string Worker::getName()
{
    return "Worker";
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