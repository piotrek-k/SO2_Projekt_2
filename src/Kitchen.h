#ifndef SO2_PROJEKT_KITCHEN
#define SO2_PROJEKT_KITCHEN

#include <vector>
#include <tuple>
#include <thread>
#include "Globals.h"
#include "Worker.h"
#include "Table.h"
#include "Cabinet.h"
#include "Fryer.h"

class Worker;

class Kitchen
{
private:
    int positionX = 10;
    int positionY = 10;

    std::vector<std::thread *> *globalThreadsContainer = new std::vector<std::thread *>();
    
    std::vector<Worker *> workers;
    std::vector<Cabinet *> cabinets;
    std::vector<Fryer* > fryers;

    int waitingOrders = 0;
    int waitingReadyIngredients = 0; // wstępnie przetworzone produkty

    std::mutex ordersMutex; // przyjęte zamówienia, czekające na realizację
    std::mutex readyIngredientsMutex;

    Table *mainTable;

    void simulationThread();

public:
    Kitchen(int positionX, int positionY, int numOfWorkers);
    ~Kitchen();

    void StartSimulation();
    void Draw();

    bool TryGetOrderToCarryOut();
    bool TryGetReadyIngredients();

    std::tuple<int, int> GetPositon()
    {
        return std::make_tuple(positionX, positionY);
    }
};

#endif //SO2_PROJEKT_KITCHEN