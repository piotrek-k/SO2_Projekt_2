#include "Table.h"
#include <curses.h>
#include <string>

Table::Table(int posX, int posY, std::vector<int> sizes, int width){
    this->posX = posX;
    this->posY = posY;
    this->tableColumnsSizes = sizes;
    this->tableWidth = width;
}

void Table::generateTable(std::vector<std::vector<std::string>> contents)
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

void Table::tableDrawHorizontalBorder(int x, int y, int width)
{
    for (int q = 0; q < width; q++)
    {
        mvaddch(y, x + q, '*');
    }
}

int Table::getColumnBeginningPos(std::vector<int> tableColumnsSizes, int tableWidth, int columnIndex)
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