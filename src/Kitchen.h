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
#include "KnivesManager.h"

class Worker;
class DeliveryManager;
class KnivesManager;
class Fryer;

class Kitchen
{
private:
    int positionX = 10;
    int positionY = 10;

    std::vector<std::thread *> *globalThreadsContainer = new std::vector<std::thread *>();

    std::vector<Worker *> workers;
    std::vector<Cabinet *> cabinets;

    atomic_queue<Order *> waitingOrders;
    atomic_queue<Order *> ordersToPrepare;
    atomic_queue<Order *> ordersToHeat;
    int waitingReadyIngredients = 0; // wstępnie przetworzone produkty

    std::mutex ordersMutex; // przyjęte zamówienia, czekające na realizację
    std::mutex readyIngredientsMutex;

    Table *mainTable;
    Table *orderQueuesTable;

    void simulationThread();

public:
    Kitchen(int positionX, int positionY, int numOfWorkers, int numOfKnives);
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

    Order *GetOrderToPrepare() { return waitingOrders.pop_and_get(); }
    bool GetOrderToPrepare(Order *o) { return waitingOrders.pop_and_get(o); }
    Order *GetHeatedOrder() { return ordersToHeat.pop_and_get(); }

    std::vector<Fryer *> fryers;

    DeliveryManager *deliveryManager;
    KnivesManager *knivesManager;

    void AddDeliveryManager(DeliveryManager *dm) { this->deliveryManager = dm; }

    std::tuple<int, int> GetPositon()
    {
        return std::make_tuple(positionX, positionY);
    }
};

#endif //SO2_PROJEKT_KITCHEN