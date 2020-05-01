#ifndef SO2_PROJEKT_FRYER
#define SO2_PROJEKT_FRYER

enum FryerState
{
    Inactive,
    WorkingAndFoodNotYetPrepared,
    WorkingAndFoodBurnt
};

class Fryer
{
private:
    void simulate();

public:
    Fryer(/* args */);
    ~Fryer();

    void LoadAndStart();
    void TurnOffTakeFood();
};

#endif //SO2_PROJEKT_FRYER
