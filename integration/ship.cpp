#include "ship.h"

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

void Ship::DrawPlayer() {
	if (!isAlive) {
		return;
	}
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
			//std::cout << "Player " << otherShip.playerNumber << " hit by Player " << playerNumber << "'s missile!\n";
			missiles[i].Disappear();
			++friendlyFire;
		}
	}
	return friendlyFire;
}