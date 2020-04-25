#include <iostream>
#include <curses.h>
#include <vector>
#include <thread>

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

int main(int argc, char *argv[])
{
	initscr(); /* Start curses mode 		  */
	start_color();
	init_pair(COLOR_ONE, COLOR_CYAN, COLOR_BLACK);

	getch();   /* Wait for user input */
	endwin();
	return 0;
}