#ifndef SO2_PROJEKT_KITCHEN
#define SO2_PROJEKT_KITCHEN

#include <vector>
#include <tuple>
#include "Worker.h"

class Kitchen
{
private:
    int positionX = 10;
    int positionY = 10;

    int tablePositionX = 55;
    int tablePositionY = 0;
    std::vector<int> tableColumnsSizes = {1, 1, 1};
    int tableWidth = 50;

    std::vector<Worker*> workers;

    void simulationThread();

public:
    Kitchen(int positionX, int positionY, int numOfWorkers);
    ~Kitchen();

    void StartSimulation();
    void Draw();

    int getColumnBeginningPos(int columnIndex);

    std::tuple<int, int> GetPositon()
    {
        return std::make_tuple(positionX, positionY);
    }
};

#endif //SO2_PROJEKT_KITCHEN