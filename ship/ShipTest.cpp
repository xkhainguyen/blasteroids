#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "fssimplewindow.h"

#include "ship.h"

int main(void) {
	int x1 = 200, y1 = 550, x2 = 600, y2 = 550;
	int windowWidth = 1024, windowHeight = 1024;
	int numberOfPlayers;
	Ship ships[2];
	while (true) {
		std::cout << "Enter number of players: ";
		std::cin >> numberOfPlayers;
		if (numberOfPlayers == 2) {
			ships[0] = Ship(x1, y1, windowWidth, windowHeight, 1);
			ships[1] = Ship(x2, y2, windowWidth, windowHeight, 2);
			break;
		}
		else if (numberOfPlayers == 1) {
			ships[0] = Ship(400, 550, windowWidth, windowHeight, 1);
			ships[1].isAlive = false;
			break;
		}
		else {
			std::cout << "Invalid number of players. Can only have 1 or 2 player mode" << std::endl;
		}
	}

	srand(time(NULL));

	FsOpenWindow(0, 0, windowWidth, windowHeight, 1);
	for (;;) {
		FsPollDevice();
		auto key = FsInkey();
		if (key == FSKEY_ESC) {
			break;
		}
		ships[0].update(key, ships[1]);
		ships[1].update(key, ships[0]);
		FsSwapBuffers();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		/*ships[0].CheckCollisionWithOtherShip(ships[1]);
		ships[1].CheckCollisionWithOtherShip(ships[0]);*/

		ships[0].draw();
		ships[1].draw();

		FsSleep(20);
	}
	for (auto& S : ships) {
		std::cout << "Player "<< S.getPlayerNumber() <<" shot " << S.missilesShot << " missiles" << std::endl;
	}
	if (ships[0].friendlyFire + ships[1].friendlyFire) {
		std::cout << "Teammates shot each other " << ships[0].friendlyFire + ships[1].friendlyFire << " times." << std::endl;
	}
	return 0;
}