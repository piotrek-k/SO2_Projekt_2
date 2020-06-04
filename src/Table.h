#ifndef SO2_PROJEKT_TABLE
#define SO2_PROJEKT_TABLE

#include <vector>
#include <string>

class Table
{
private:
    int posX = 55;
    int posY = 0;
    std::vector<int> tableColumnsSizes = {1, 1, 1};
    int tableWidth = 50;

public:
    Table(int posX, int posY, std::vector<int> sizes, int width);
    ~Table();

    static void tableDrawHorizontalBorder(int x, int y, int width);
    static int getColumnBeginningPos(std::vector<int> tableColumnsSizes, int tableWidth, int columnIndex);
    void generateTable(std::vector<std::string> columnNames, std::vector<std::vector<std::string>> contents);
};

#endif //SO2_PROJEKT_TABLE