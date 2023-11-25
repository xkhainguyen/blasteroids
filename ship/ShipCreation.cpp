#include "ship.h"
#include <iostream>

void Missile::activateMissile(int startingx, int startingy) {
	isActive = true;
	xCoord = startingx;
	yCoord = startingy;
}

void Missile::shoot() {
	if (!isActive) {
		return;
	}
	xCoord = xCoord;
	yCoord = yCoord + velocity;
	if (yCoord < 0)
	{
		disappear();
	}
}

void Missile::disappear(void) {
	isActive = false;
}

void Missile::draw(void) {
	if (!isActive) {
		return;
	}
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2i(xCoord, yCoord);
	glVertex2i(xCoord, yCoord + size);
	glEnd();
}

void Ship::drawPlayer() {
	if (!isAlive) {
		return;
	}
	glColor3f(0, 0, 0);

	glBegin(GL_POLYGON);
	for (int i = 0; i < 64; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(64);
		float x = 30.0 * cosf(theta);
		float y = 15.0 * sinf(theta);
		glVertex2f(x + xCoord, y + yCoord);
	}
	glEnd();

	glColor3f(1, 1, 0);

	float radius = 10.0f;  // Fix the radius to 10 pixels
	glBegin(GL_POLYGON);
	for (int i = 0; i < 64; i++) {
		float theta = 2.0f * 3.1415926f * float(i) / float(64);
		float x = radius * cosf(theta);
		float y = radius * sinf(theta);
		glVertex2f(x + xCoord, y + yCoord);
	}
	glEnd();

	float angleIncrement = 2.0f * 3.1415926f / 6;

	for (int i = 0; i < 6; i++) {
		float angle = i * angleIncrement;
		float rx = 20.0 * cosf(angle);
		float ry = 15.0 * sinf(angle);

		float red = static_cast<float>(rand()) / RAND_MAX;
		float green = static_cast<float>(rand()) / RAND_MAX;
		float blue = static_cast<float>(rand()) / RAND_MAX;

		glColor3f(red, green, blue); 
		glBegin(GL_POLYGON);
		for (int i = 0; i < 64; i++) {
			float theta = 2.0f * 3.1415926f * float(i) / float(64);
			float x = rx + 2.0f * cosf(theta);
			float y = ry + 2.0f * sinf(theta);
			glVertex2f(x + xCoord, y + yCoord);
		}
		glEnd();
	}
}

void Ship::shootMissile() {
	if (!isAlive) {
		return;
	}
	for (int i = 0; i < numOfMissiles; ++i) {
		missiles[i].shoot();
		missiles[i].draw();
	}
}

void Ship::triggerMissile() {
	if (!isAlive) {
		return;
	}
	for (int i = 0; i < numOfMissiles; ++i) {
		if (!missiles[i].isActive) {
			missiles[i].activateMissile(xCoord, yCoord);
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
int Ship::getPlayerNumber(void) {
	return playerNumber;
}

void Ship::moveShipLeft(void)
{
	if (!isAlive) {
		return;
	}
	xCoord -= 15;
	if (xCoord < 0)
	{
		xCoord = 800;
	}
}
void Ship::moveShipRight() {
	if (!isAlive) {
		return;
	}
	xCoord += 15;
	if (xCoord > 800)
	{
		xCoord = 0;
	}
}
void Ship::moveShipUp() {
	if (!isAlive) {
		return;
	}
	if (yCoord > 30) {
		yCoord -= 15;
	}
}
void Ship::moveShipDown() {
	if (!isAlive) {
		return;
	}
	if (yCoord < 570) {
		yCoord += 15;
	}
}

bool Ship::checkCollisionWithMissile(Missile missile) {
	return (
		xCoord - width <= missile.xCoord &&
		missile.xCoord <= xCoord + width &&
		yCoord <= missile.yCoord &&
		missile.yCoord <= yCoord + height
		);
}

bool Ship::checkCollisionWithOtherShip(Ship otherShip) {
	if (xCoord < otherShip.xCoord + 30 && xCoord > otherShip.xCoord - 30) {
		if (yCoord < otherShip.yCoord + 15 && yCoord > otherShip.yCoord - 15) {
			/*std::cout << "Overlap" << std::endl;
			std::cout << "Ship 1 coordinates: (" << xCoord << ", " << yCoord << ")" << std::endl;
			std::cout << "Ship 0 coordinates: (" << otherShip.xCoord << ", " << otherShip.yCoord << ")" << std::endl;*/
			/*xCoord = xCoord;
			yCoord = yCoord;*/
			return true;
		}
	}
	return false;
}

void Ship::checkCollisionWithOtherShipMissiles(Ship& otherShip) {
	for (int i = 0; i < otherShip.numOfMissiles; ++i) {
		if (missiles[i].isActive && otherShip.checkCollisionWithMissile(missiles[i])) {
			//std::cout << "Player " << otherShip.playerNumber << " hit by Player " << playerNumber << "'s missile!\n";
			missiles[i].disappear();
			++friendlyFire;
			otherShip.isAlive = false;
			otherShip.xCoord = -500;
		}
	}
}

void Ship::update(int key, Ship& otherShip) {
	if (playerNumber == 1) {
		if (key == FSKEY_ESC) {
			return;
		}
		switch (key)
		{
		case FSKEY_LEFT:
			moveShipLeft();
			return;
		case FSKEY_RIGHT:
			moveShipRight();
			return;
		case FSKEY_UP:
			moveShipUp();
			return;
		case FSKEY_DOWN:
			moveShipDown();
			return;
		case FSKEY_SPACE:
			triggerMissile();
			return;
		}
	}
	else {
		switch (key) {
		case FSKEY_A:
			moveShipLeft();
			return;
		case FSKEY_D:
			moveShipRight();
			return;
		case FSKEY_W:
			moveShipUp();
			return;
		case FSKEY_S:
			moveShipDown();
			return;
		case FSKEY_Q:
			triggerMissile();
			return;
		}
	}
	checkCollisionWithOtherShipMissiles(otherShip);
}

void Ship::draw(void) {
	drawPlayer();
	shootMissile();
}