#ifndef SO2_PROJEKT_CUSTOMER
#define SO2_PROJEKT_CUSTOMER

enum CustomerState {
    NoAction,
    WaitingForOrder
};

class Customer
{
private:
    CustomerState state = NoAction;

    int locationX = 0;
    int locationY = 0;
    int orderFreq = 0;

    int waitingTime = 0;

    void makeOrder();
    void simulatingThread();

public:
    Customer(int orderFreq);
    ~Customer();

    void StartSimulation();
    void MarkOrderAsCompleted();
};

#endif //SO2_PROJEKT_CUSTOMER