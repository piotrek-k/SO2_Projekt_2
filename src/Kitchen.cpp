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

void Kitchen::generateTable(std::vector<std::vector<std::string>> contents,
                            std::vector<int> tableColumnsSizes, int posX,
                            int posY, int tableWidth)
{
    int currentLinePosVertical = posY;
    int currentLinePosHorizontal = posX;

    tableDrawHorizontalBorder(posX, currentLinePosVertical, tableWidth);

    currentLinePosVertical++;

    for (auto &row : contents)
    {
        int colIndex = 0;
        for (auto &col : row)
        {
            currentLinePosHorizontal =
                posX + getColumnBeginningPos(tableColumnsSizes, tableWidth, colIndex);

            mvaddch(currentLinePosVertical,
                    currentLinePosHorizontal, '*');

            mvprintw(currentLinePosVertical, currentLinePosHorizontal + 1,
                     " %s", col.c_str());

            colIndex++;
        }

        currentLinePosHorizontal = posX + tableWidth - 1;
        mvaddch(currentLinePosVertical,
                currentLinePosHorizontal, '*');

        currentLinePosVertical++;
    }

    tableDrawHorizontalBorder(posX, currentLinePosVertical, tableWidth);
}

void Kitchen::tableDrawHorizontalBorder(int x, int y, int width)
{
    for (int q = 0; q < width; q++)
    {
        mvaddch(y, x + q, '*');
    }
}

void Kitchen::Draw()
{
    std::vector<std::vector<std::string>> contents;

    for(auto &w: workers){
        std::vector<std::string> row;
        row.push_back(w->getName());
        row.push_back(w->getStateName());
        row.push_back("Random text");
        contents.push_back(row);
    }

    generateTable(contents, tableColumnsSizes, tablePositionX, tablePositionY, tableWidth);
}

void Kitchen::simulationThread()
{
}

int Kitchen::getColumnBeginningPos(std::vector<int> tableColumnsSizes, int tableWidth, int columnIndex)
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