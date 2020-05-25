#include "Kitchen.h"
#include "Globals.h"
#include "Worker.h"

#include <curses.h>

Kitchen::Kitchen(int positionX, int positionY, int numOfWorkers)
{
    this->positionX = positionX;
    this->positionY = positionY;

    for (int w = 0; w < numOfWorkers; w++)
    {
        workers.push_back(new Worker());
    }
}

void Kitchen::StartSimulation()
{
}

void Kitchen::Draw()
{
    int currentLinePosVertical = this->tablePositionY;
    int currentLinePosHorizontal = this->tablePositionX;

    for (int x = 0; x < tableWidth; x++)
    {
        mvaddch(this->tablePositionY,
                this->tablePositionX + x, '*');
    }

    currentLinePosVertical++;

    for (auto &w : workers)
    {
        currentLinePosHorizontal =
            this->tablePositionX + getColumnBeginningPos(0);

        mvaddch(currentLinePosVertical,
                currentLinePosHorizontal, '*');

        mvprintw(currentLinePosVertical, currentLinePosHorizontal + 1,
                 " %s", w->getName().c_str());

        currentLinePosHorizontal =
            this->tablePositionX + getColumnBeginningPos(1);

        mvaddch(currentLinePosVertical,
                currentLinePosHorizontal, '*');

        mvprintw(currentLinePosVertical, currentLinePosHorizontal + 1,
                 " %s", w->getStateName().c_str());

        currentLinePosHorizontal = this->tablePositionX + this->tableWidth - 1;
        mvaddch(currentLinePosVertical,
                currentLinePosHorizontal, '*');

        currentLinePosVertical++;
    }

    currentLinePosHorizontal = this->tablePositionX;
    for (int x = 0; x < tableWidth; x++)
    {
        mvaddch(currentLinePosVertical,
                currentLinePosHorizontal + x, '*');
    }
}

void Kitchen::simulationThread()
{
}

int Kitchen::getColumnBeginningPos(int columnIndex)
{

    int sum = 0;
    int currentMove = 0;
    //std::vector<int> moves;

    for (int c = 0; c < tableColumnsSizes.size(); c++)
    {
        sum += tableColumnsSizes[c];
    }

    for (int c = 0; c < tableColumnsSizes.size(); c++)
    {
        if (c == columnIndex)
        {
            return currentMove;
        }

        currentMove += tableWidth / sum * tableColumnsSizes[columnIndex];
    }

    return -1;
}