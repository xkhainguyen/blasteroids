#include "ship.h"
#include <iostream>

#define Pi 3.14159265358979323846

void Missile::activateMissile(int startingx, int startingy) {
	isActive = true;
	xCoord = startingx;
	yCoord = startingy;
}

void Missile::shoot() {
	if (!isActive) {
		return;
	}

	double ang = startingDegreeAngle * Pi / 180;

	xCoord -= velocity*sin(ang);
	yCoord += velocity*cos(ang);

	if (yCoord < 0||yCoord > 600||xCoord >800||xCoord <0)
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
	double ang = startingDegreeAngle * Pi / 180;
	double s = sin(ang);
	double c = cos(ang);

	glColor3f(1, 0, 0);
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0f);
	glBegin(GL_POINTS);
	glVertex2i(xCoord, yCoord);
	glDisable(GL_POINT_SMOOTH);
	glEnd();
}

void Ship::drawPlayer() {
	if (!isAlive) {
		return;
	}
	{
		double ang = degAng * Pi / 180;
		double s = sin(ang);
		double c = cos(ang);

		int centerX = xCoord;
		int centerY = yCoord;
		// Set spaceship body color
		glColor3f(0.8f, 0.8f, 0.8f); // Light gray
		// Draw the spaceship body (main body)
		glBegin(GL_QUADS);

		glVertex2d(centerX - width * c * .5 + height * s * .5, centerY - height * c * .5 - width * s * .5);
		// Upper right corner
		glVertex2d(centerX + width * c * .5 + height * s * .5, centerY - height * c * .5 + width * s * .5);
		// Lower right corner
		glVertex2d(centerX + width * c * .5 - height * s * .5, centerY + height * c * .5 + width * s * .5);
		// Lower left corner
		glVertex2d(centerX - width * c * .5 - height * s * .5, centerY + height * c * .5 - width * s * .5);
		glEnd();
		// Set fins' color
		glColor3f(0.5f, 0.5f, 0.5f); // Dark gray
		// Draw the triangular fins on the sides
		glBegin(GL_TRIANGLES);
		// Left fin (triangle)
		glVertex2d(centerX - width * c * .5 - height * s * .5, centerY + height * c * .5 - width * s * .5); // Bottom vertex
		glVertex2d(centerX - (width * .5 + finWidth) * c - height * s * .5, centerY + height * c * .5 - (width * .5 + finWidth) * s); // Middle vertex
		glVertex2d(centerX - width * c * .5 - (height * .5 - finHeight) * s, centerY + (height * .5 - finHeight) * c - width * s * .5); // Top vertex
		// Right fin (triangle)
		glVertex2d(centerX + width * c * .5 - height * s * .5, centerY + height * c * .5 + width * s * .5); // Bottom vertex
		glVertex2d(centerX + (width * .5 + finWidth) * c - height * s * .5, centerY + height * c * .5 + (width * .5 + finWidth) * s); // Middle vertex
		glVertex2d(centerX + width * c * .5 - (height * .5 - finHeight) * s, centerY + (height * .5 - finHeight) * c + width * s * .5); // Top vertex
		glEnd();
		// Set nose color
		//glColor3f(1.0f, 1.0f, 1.0f); // White
		glColor3f(0.5f, 0.5f, 0.5f);
		// Draw the nose cone (triangle)
		glBegin(GL_TRIANGLES);
		// Top vertex of the nose cone
		glVertex2d(centerX + (height * .5 + noseHeight) * s, centerY - (height * .5 + noseHeight) * c);
		// Left vertex of the nose cone
		glVertex2d(centerX - width * c * .5 + height * s * .5, centerY - height * c * .5 - width * s * .5);
		// Right vertex of the nose cone
		glVertex2d(centerX + width * c * .5 + height * s * .5, centerY - height * c * .5 + width * s * .5);
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
			missiles[i].startingDegreeAngle = degAng;
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
	degAng -= 10;
	if (xCoord < 0)
	{
		xCoord = 800;
	}

}
void Ship::moveShipRight(void) {
	if (!isAlive) {
		return;
	}
	degAng += 10;
	if (xCoord > 800)
	{
		xCoord = 0;
	}
}
void Ship::moveShipUp(void) {
	if (!isAlive) {
		return;
	}
	if (yCoord > 30) {
		yCoord -= 15;
	}
}
void Ship::moveShipDown(void) {
	if (!isAlive) {
		return;
	}
	if (yCoord < 570) {
		yCoord += 15;
	}
}

void Ship::flyShip(void)
{
	double ang = degAng * Pi / 180;
	double s = sin(ang);
	double c = cos(ang);

	if ((0!= FsGetKeyState(FSKEY_UP)) || (0!=FsGetKeyState(FSKEY_W)))
	{
		velY -= 0.3 * c;
		velX += 0.3 * s;

		// ... existing flame drawing code ...

		// Add thrusting effect
		int numFlames = 200;  // number of flames to generate
		glBegin(GL_LINES);
		for (int i = 0; i < numFlames; ++i)
		{
			// Randomize the color to shades of red and orange
			unsigned char red = 200 + rand() % 56;  // 200 to 255
			unsigned char green = 50 + rand() % 56; // 50 to 105
			unsigned char blue = 0;                 // 0
			glColor3ub(red, green, blue);
			// Calculate the start point for flame (back of the spaceship)
			int randstart = rand() % width;
			int xf1 = xCoord - width * c / 2 - (height * .5 + finHeight) * s + randstart * c; // Adjusted for center reference
			int yf1 = yCoord - width * s / 2 + (height * .5 + finHeight) * c + randstart * s; // Adjusted for center reference
			// Randomize the length and direction of the flame lines
			int length = rand() % 20 + 10;  // flame length between 10 and 30 (adjust as needed)
			double flameAngle = ang + (rand() % 20 - 10) * Pi / 180; // Random angle deviation
			double flameS = sin(flameAngle);
			double flameC = cos(flameAngle);
			// Calculate the end point of the line
			int xf2 = xf1 - flameS * length;
			int yf2 = yf1 + length * flameC;
			// Draw the line
			glVertex2i(xf1, yf1);
			glVertex2i(xf2, yf2);
		}
		glEnd();
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
	if (xCoord < 0)
	{
		xCoord += 800;
	}
	else if (xCoord >= 800)
	{
		xCoord -= 800;
	}

	if (yCoord < 0)
	{
		yCoord += 600;
	}
	else if (yCoord >= 600)
	{
		yCoord -= 600;
	}

	xCoord += velX;
	yCoord += velY;
	if (playerNumber == 1) {
		if (0 != FsGetKeyState(FSKEY_ESC)) {
			return;
		}
		if (0 != FsGetKeyState(FSKEY_LEFT)) {
			moveShipLeft();
		}
		if (0 != FsGetKeyState(FSKEY_RIGHT)) {
			moveShipRight();
		}
		if (0 != FsGetKeyState(FSKEY_UP)) {
			flyShip();
			// soundManager.PlayThrust();
		}
		if (key == FSKEY_SPACE) {
			triggerMissile();
			// soundManager.PlayShoot();
		}
	}
	else {
		if (0 != FsGetKeyState(FSKEY_A)) {
			moveShipLeft();
		}
		if (0 != FsGetKeyState(FSKEY_D)) {
			moveShipRight();
		}
		if (0 != FsGetKeyState(FSKEY_W)) {
			flyShip();
			// soundManager.PlayThrust();
		}
		if (key == FSKEY_Q) {
			triggerMissile();
			// soundManager.PlayShoot();
		}
	}
	checkCollisionWithOtherShipMissiles(otherShip);
}

void Ship::draw(void) {
	drawPlayer();
	shootMissile();
}