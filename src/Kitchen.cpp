#include "Kitchen.h"
#include "Globals.h"
#include "Worker.h"
#include "Table.h"

#include <curses.h>

Kitchen::Kitchen(int positionX, int positionY, int numOfWorkers)
{
    this->positionX = positionX;
    this->positionY = positionY;

    for (int w = 0; w < numOfWorkers; w++)
    {
        workers.push_back(new Worker());
    }

    mainTable = new Table(55, 1, std::vector<int>{1, 1, 1}, 50);
}

void Kitchen::StartSimulation()
{
    bool stopSignal = false;

    for (auto &w : workers)
    {
        w->StartSimulation(&stopSignal);
    }
}

void Kitchen::Draw()
{
    std::vector<std::vector<std::string>> contents;

    for (auto &w : workers)
    {
        std::vector<std::string> row;
        row.push_back(w->getName());
        row.push_back(w->getStateName());
        row.push_back("Random text");
        contents.push_back(row);
    }

    mainTable->generateTable(contents);
}

void Kitchen::simulationThread()
{
}