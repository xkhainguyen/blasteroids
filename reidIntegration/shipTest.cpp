#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "fssimplewindow.h"

#include "ship.h"

int main(void) {
	int x1 = 200, y1 = 550, x2 = 600, y2 = 550;
	int friendlyFire = 0;
	int windowWidth = 800, windowHeight = 600;
	Ship ships[2] = { Ship(x1, y1, windowWidth, windowHeight, 1), Ship(x2, y2, windowWidth, windowHeight, 2) };

	srand(time(NULL));

	FsOpenWindow(0, 0, windowWidth, windowHeight, 1);
	for (;;) {
		FsPollDevice();
		auto key = FsInkey();
		if (key == FSKEY_ESC) {
			break;
		}
		switch (key)
		{
		case FSKEY_LEFT:
			ships[0].moveShipLeft();
			break;
		case FSKEY_RIGHT:
			ships[0].moveShipRight();
			break;
		case FSKEY_UP:
			ships[0].moveShipUp();
			break;
		case FSKEY_DOWN:
			ships[0].moveShipDown();
			break;
		case FSKEY_SPACE:
			ships[0].TriggerMissile();
			break;

		case FSKEY_A:
			ships[1].moveShipLeft();
			break;
		case FSKEY_D:
			ships[1].moveShipRight();
			break;
		case FSKEY_W:
			ships[1].moveShipUp();
			break;
		case FSKEY_S:
			ships[1].moveShipDown();
			break;
		case FSKEY_Q:
			ships[1].TriggerMissile();
			break;
		}

		friendlyFire += ships[0].CheckCollisionWithOtherShipMissiles(ships[1]);
		friendlyFire += ships[1].CheckCollisionWithOtherShipMissiles(ships[0]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ships[0].DrawPlayer();
		ships[1].DrawPlayer();

		for (auto& ship : ships) {
			ship.ShootMissile();
		}

		FsSwapBuffers();
		FsSleep(20);
	}
	for (auto& S : ships) {
		std::cout << "Player 1 shot " << S.missilesShot << " missiles" << std::endl;
	}
	std::cout << "Teammates shot each other " << friendlyFire << " times." << std::endl;
	return 0;
}