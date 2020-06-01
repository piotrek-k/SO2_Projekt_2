#ifndef SO2_PROJEKT_KITCHEN
#define SO2_PROJEKT_KITCHEN

#include <vector>
#include <tuple>
#include <thread>
#include <queue>
#include "Globals.h"
#include "Worker.h"
#include "Table.h"
#include "Cabinet.h"
#include "Fryer.h"
#include "Order.h"
#include "others/atomic_queue.h"

class Worker;

class Kitchen
{
private:
    int positionX = 10;
    int positionY = 10;

    std::vector<std::thread *> *globalThreadsContainer = new std::vector<std::thread *>();

    std::vector<Worker *> workers;
    std::vector<Cabinet *> cabinets;
    std::vector<Fryer *> fryers;

    atomic_queue<Order *> waitingOrders;
    atomic_queue<Order *> ordersToPrepare;
    atomic_queue<Order *> ordersToHeat;
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

    Order *TryGetOrderToCarryOut();
    bool TryGetReadyIngredients();
    void AddNewReadyIngredient();

    void PassNewOrder(Order *o);
    void PassOrderToPrepare(Order *o) { ordersToPrepare.push(o); }
    void PassOrderToHeat(Order *o) { ordersToHeat.push(o); }

    int GetWaitingOrdersNumber() { return waitingOrders.size(); }
    int GetNumberOfOrdersToPrepare() { return ordersToPrepare.size(); }
    int GetOrdersToHeat() { return ordersToHeat.size(); }
    int GetReadyIngredientsNumber() { return waitingReadyIngredients; }

    Order* GetOrderToPrepare(){ return ordersToPrepare.pop_and_get(); }

    std::tuple<int, int> GetPositon()
    {
        return std::make_tuple(positionX, positionY);
    }
};

#endif //SO2_PROJEKT_KITCHEN