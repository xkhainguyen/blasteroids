#pragma once

#ifndef SHIP_H
#define SHIP_H

#include "fssimplewindow.h"
#include <cmath>

class Missile {
public:
	int xCoord, yCoord, velocity = -10;
	bool isActive = false;
	int size = 10;

	void activateMissile(int startingx, int startingy);
	void shoot();
	void disappear(void);
	void draw(void);
};

class Ship {
public:
	Ship() : xCoord(0), yCoord(0), maxXCoord(800), maxYCoord(600), playerNumber(0) {}
	Ship(int initialX, int initialY, int maxX, int maxY, int playerNum) : xCoord(initialX), yCoord(initialY), maxXCoord(maxX), maxYCoord(maxY), playerNumber(playerNum) {}
	Missile missiles[10];
	int numOfMissiles = 10;
	int playerNumber;
	int xCoord, yCoord, missilesShot = 0;
	bool isAlive = true;
	bool overlap = false;
	int maxXCoord, maxYCoord;
	int friendlyFire = 0;

	int width = 15, height = 10;
	void drawPlayer();
	void shootMissile();
	void triggerMissile();
	bool checkCollisionWithMissile(Missile m);
	bool checkCollisionWithOtherShip(Ship otherShip);
	void checkCollisionWithOtherShipMissiles(Ship& otherShip);
	int getShipxCoordinate(void);
	int getShipyCoordinate(void);
	int getPlayerNumber(void);
	void moveShipLeft(void);
	void moveShipRight(void);
	void moveShipUp(void);
	void moveShipDown(void);
	void update(int key, Ship& otherShip);
	void draw(void);
};

#endif 
