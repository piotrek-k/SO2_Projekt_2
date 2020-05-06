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

    std::vector<Worker> workers;

    void simulationThread();

public:
    Kitchen(int positionX, int positionY);
    ~Kitchen();

    void StartSimulation();
    void Draw();

    std::tuple<int, int> GetPositon()
    {
        return std::make_tuple(positionX, positionY);
    }
};

#endif //SO2_PROJEKT_KITCHEN