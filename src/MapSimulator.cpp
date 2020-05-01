#include "MapSimulator.h"

MapSimulator::MapSimulator(int sizeX, int sizeY, Kitchen* kitchen,
                 int numOfDeliverymans, int numOfClients, int clientOrderFrequency){
    this->sizeX = sizeX;
    this->sizeY = sizeY;
    this->kitchenRef = kitchen;
    
    for(int d=0; d<numOfDeliverymans; d++){
        allDeliverymans.push_back(new Deliveryman());
    }

    for(int d=0; d<numOfClients; d++){
        allCustomers.push_back(new Customer(clientOrderFrequency));
    }
}

MapSimulator::~MapSimulator(){

}

void MapSimulator::StartSimulation(){

}

void MapSimulator::Draw(){

}

void MapSimulator::simulationThread(){

}