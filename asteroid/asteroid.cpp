#include "asteroid.hpp"

// Constructor implementation
Asteroid::Asteroid(double x, double y, double vx, double vy, double radius, int breakUpCount)
    : x(x), y(y), vx(vx), vy(vy), radius(radius), isActive(true), breakUpCount(breakUpCount) {}

// Update the position of the asteroid
void Asteroid::updatePosition() {
    x += vx;
    y += vy;
}

// Simulate breaking up the asteroid
int Asteroid::breakUp() {
    isActive = false; // For simplicity, just deactivate the asteroid

    // // Change color to white: pseudo-explosion
    // glColor3f(1.0, 1.0, 1.0);

    // // Draw the asteroid
    // glBegin(GL_POLYGON);
    // for(int i = 0; i < 360; i++) {
    //     float degInRad = i * M_PI / 180.0;
    //     glVertex2f(x + cos(degInRad) * radius, y + sin(degInRad) * radius);
    // }
    // glEnd();
    // Add explosion animation here
    //IDEA: make it still for some time
    

    return breakUpCount;
}

// Draw the asteroid
void Asteroid::drawAsteroid() const {
    if (isActive) {
        glColor3f(0.5f, 0.5f, 0.5f); // Set color to gray
        glBegin(GL_POLYGON);
        for(int i = 0; i < 360; i++) {
            float degInRad = i * M_PI / 180.0f;
            glVertex2f(x + cos(degInRad) * radius, y + sin(degInRad) * radius);
        }
        glEnd();
    }
}

// Get the active state of the asteroid
bool Asteroid::getState() const {
    return isActive;
}

std::pair<double,double> Asteroid::getPosition() const {
    return std::make_pair(x, y);
}

// String representation for debugging
std::string Asteroid::toString() const {
    return "Asteroid at (" + std::to_string(x) + ", " + std::to_string(y) +
           ") with velocity (" + std::to_string(vx) + ", " + std::to_string(vy) + ")";
}
