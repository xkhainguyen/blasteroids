#include <iostream>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "fssimplewindow.h"

class Missile {
public:
	int xCoord, yCoord, velocity = -10;
	bool isActive = false;
	int size = 10;
	void ActivateMissile(int startingx, int startingy);
	void Shoot();
	void Disappear(void);
	void Draw(void);
};

void Missile::ActivateMissile(int startingx, int startingy) {
	isActive = true;
	xCoord = startingx;
	yCoord = startingy;
}

void Missile::Shoot() {
	if (!isActive) {
		return;
	}
	xCoord = xCoord;
	yCoord = yCoord + velocity;
	if (yCoord < 0)
	{
		Disappear();
	}
}

void Missile::Disappear(void) {
	isActive = false;
}

void Missile::Draw(void) {
	if (!isActive) {
		return;
	}
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(xCoord, yCoord);
	glVertex2i(xCoord, yCoord + size);
	glEnd();
}

class Ship {
public:
	Ship(int initialX, int initialY, int maxX, int maxY, int playerNum) : xCoord(initialX), yCoord(initialY), maxXCoord(maxX), maxYCoord(maxY), playerNumber(playerNum) {}
	Missile missiles[10];
	int numOfMissiles = 10;
	int playerNumber;
	int xCoord, yCoord, missilesShot = 0;
	bool isAlive = true;
	int maxXCoord, maxYCoord;
	int width = 15, height = 10;
	void DrawPlayer();
	void ShootMissile();
	void TriggerMissile();
	bool CheckCollisionWithMissile(Missile m);
	int CheckCollisionWithOtherShipMissiles(Ship otherShip);
	int getShipxCoordinate(void);
	int getShipyCoordinate(void);
	void moveShipLeft(void);
	void moveShipRight(void);
	void moveShipUp(void);
	void moveShipDown(void);
};

void Ship::DrawPlayer() {
	//isAlive = 1;
	glColor3f(0, 1, 0);

	glBegin(GL_QUADS);

	glVertex2i(xCoord - width, yCoord);
	glVertex2i(xCoord + width, yCoord);
	glVertex2i(xCoord + width, yCoord - height);
	glVertex2i(xCoord - width, yCoord - height);

	glVertex2i(xCoord - 5, yCoord - 20);
	glVertex2i(xCoord - 5, yCoord);
	glVertex2i(xCoord + 5, yCoord);
	glVertex2i(xCoord + 5, yCoord - 20);

	glEnd();

	/*for (int i = 0; i < numOfMissiles; ++i) {
		missiles[i].Draw();
	}*/
}

void Ship::ShootMissile() {
	for (int i = 0; i < numOfMissiles; ++i) {
		missiles[i].Shoot();
		missiles[i].Draw();
	}
}

void Ship::TriggerMissile() {
	for (int i = 0; i < numOfMissiles; ++i) {
		if (!missiles[i].isActive) {
			missiles[i].ActivateMissile(xCoord, yCoord);
			++missilesShot;
			break;
		}
	}
}

int Ship::getShipxCoordinate(void) {
	return xCoord;
}
int Ship::getShipyCoordinate(void) {
	return yCoord;
}

void Ship::moveShipLeft(void)
{
	xCoord -= 15;
	if (xCoord < 0)
	{
		xCoord = 800;
	}
}
void Ship::moveShipRight() {
	xCoord += 15;
	if (xCoord > 800)
	{
		xCoord = 0;
	}
}
void Ship::moveShipUp() {
	if (yCoord > 30) {
		yCoord -= 15;
	}
}
void Ship::moveShipDown() {
	if (yCoord < 570) {
		yCoord += 15;
	}
}

bool Ship::CheckCollisionWithMissile(Missile missile) {
	return (
		xCoord - width <= missile.xCoord &&
		missile.xCoord <= xCoord + width &&
		yCoord <= missile.yCoord &&
		missile.yCoord <= yCoord + height
		);
}

int Ship::CheckCollisionWithOtherShipMissiles(Ship otherShip) {
	int friendlyFire = 0;
	for (int i = 0; i < otherShip.numOfMissiles; ++i) {
			if (missiles[i].isActive && otherShip.CheckCollisionWithMissile(missiles[i])) {
				std::cout << "Player "<< otherShip.playerNumber <<" hit by Player "<< playerNumber <<"'s missile!\n";
				missiles[i].Disappear();
				++friendlyFire;
			}
	}
	return friendlyFire;
}


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
		

		/*for (auto& missile : ships[0].missiles) {
			if (missile.isActive && missile.yCoord < ships[0].yCoord - 20) {
				if (missile.isActive && ships[1].CheckCollisionWithMissile(missile)) {
					std::cout << "Player 2 hit by Player 1's missile!\n";
					missile.Disappear();
					++friendlyFire;
				}
			}
		}*/

		/*for (auto& missile : ships[1].missiles) {
			if (missile.isActive && missile.yCoord < ships[1].yCoord - 20) {
				if (missile.isActive && ships[0].CheckCollisionWithMissile(missile)) {
					std::cout << "Player 1 hit by Player 2's missile!\n";
					missile.Disappear();
					++friendlyFire;
				}
			}
		}*/

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

