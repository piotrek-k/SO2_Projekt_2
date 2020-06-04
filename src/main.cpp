#include <iostream>
#include <curses.h>
#include <vector>
#include <thread>

#include "DeliveryManager.h"

#include "Globals.h"

static void waitForKey(bool *threadStop)
{
	while (true)
	{
		char key = getch();
		if (key == 'q' || key == 27)
		{
			*threadStop = true;
		}
	}
}

std::vector<std::thread *> *globalThreadsContainer = new std::vector<std::thread *>();

int main(int argc, char *argv[])
{

	int numofWorkers = 5;
	int numOfKnives = 2;
	int numOfDeliverymans = 3;
	int numOfClients = 10;
	int orderFreq = 5;

	if (argc < 6)
	{
		std::cout << "[numofWorkers][numOfKnives][numOfDeliverymans][numOfClients][orderFreq]" << std::endl;
	}
	else
	{
		numofWorkers = atoi(argv[1]);
		numOfKnives = atoi(argv[2]);
		numOfDeliverymans = atoi(argv[3]);
		numOfClients = atoi(argv[4]);
		orderFreq = atoi(argv[5]);
	}

	initscr(); /* Start curses mode 		  */
	start_color();
	init_pair(MAP_BACKGROUND, COLOR_WHITE, COLOR_CYAN);
	init_pair(MAP_CLIENT, COLOR_WHITE, COLOR_YELLOW);
	init_pair(MAP_CLIENT_ACTIVE, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(MAP_DELIVERYMAN, COLOR_WHITE, COLOR_CYAN);
	init_pair(MAP_KITCHEN, COLOR_WHITE, COLOR_RED);
	init_pair(TABLE_DEFAULT, COLOR_WHITE, COLOR_CYAN);

	Kitchen *kitchen = new Kitchen(15, 15, numofWorkers, numOfKnives);
	DeliveryManager *map = new DeliveryManager(50, 30, kitchen, numOfDeliverymans, numOfClients, orderFreq, globalThreadsContainer);
	kitchen->AddDeliveryManager(map);

	map->StartSimulation();
	kitchen->StartSimulation();

	bool appStop = false;
	std::thread *n_t = new std::thread(waitForKey, &appStop);
	while (!appStop)
	{
		clear();

		map->Draw();
		kitchen->Draw();

		int position = 32;
		//mvprintw(position, 5, "Waiting orders: %d", map->waitingOrdersToDeliver.size());
		//mvprintw(position+1, 5, "Waiting deliverymen: %d", map->waitingDeliverymans.size());

		refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	//getch(); /* Wait for user input */
	endwin();
	return 0;
}