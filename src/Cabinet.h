#ifndef SO2_PROJEKT_CABINET
#define SO2_PROJEKT_CABINET

#include <mutex>

class Cabinet
{
private:
    int ingredientSets = 0;
    std::mutex mtx;

public:
    Cabinet(/* args */);
    ~Cabinet();

    bool TryGetFood();
};

#endif //SO2_PROJEKT_CABINET