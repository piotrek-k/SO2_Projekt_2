#include <iostream>
#include <curses.h>
#include <vector>
#include <thread>

#include "MapSimulator.h"

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

std::vector<std::thread*> *globalThreadsContainer = new std::vector<std::thread*>();

int main(int argc, char *argv[])
{
	initscr(); /* Start curses mode 		  */
	start_color();
	init_pair(MAP_BACKGROUND, COLOR_WHITE, COLOR_CYAN);
	init_pair(MAP_CLIENT, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(MAP_DELIVERYMAN, COLOR_WHITE, COLOR_CYAN);
	init_pair(TABLE_DEFAULT, COLOR_WHITE, COLOR_CYAN);

	Kitchen* kitchen = new Kitchen();
	DeliveryManager* map = new DeliveryManager(50, 30, kitchen, 10, 10, 1, globalThreadsContainer);

	map->StartSimulation();

	bool appStop = false;
	std::thread *n_t = new std::thread(waitForKey, &appStop);
	while (!appStop)
	{
		clear();

		map->Draw();
		kitchen->Draw();

		refresh();

		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	getch(); /* Wait for user input */
	endwin();
	return 0;
}