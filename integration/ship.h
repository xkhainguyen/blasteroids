#pragma once

#ifndef SHIP_H
#define SHIP_H

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

#endif 
