#ifndef SO2_PROJEKT_DELIVERYMAN
#define SO2_PROJEKT_DELIVERYMAN

enum DeliverymanState {
    WaitingForOrders,
    DeliveringOrder,
    ComingBack
};

class Deliveryman
{
private:
    DeliverymanState state = WaitingForOrders;

    int positionX = 0;
    int positionY = 0;

    void simulateDelivery();

public:
    Deliveryman(/* args */);
    ~Deliveryman();

    void GiveOrder();
};


#endif //SO2_PROJEKT_DELIVERYMAN