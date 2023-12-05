#include "asteroid.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Define a struct for RGB colors
struct RGBColor {
    float r, g, b;
};

// Define the color palette
static const std::vector<RGBColor> colorPalette = {
    {1.0f, 0.0f, 0.0f}, // Red
    {0.0f, 1.0f, 0.0f}, // Green
    {0.0f, 0.0f, 1.0f}, // Blue
    {1.0f, 1.0f, 0.0f}, // Yellow
    {1.0f, 0.0f, 1.0f}, // Magenta
    {0.0f, 1.0f, 1.0f}, // Cyan
    {1.0f, 0.5f, 0.0f}, // Orange
};

// Constructor implementation
Asteroid::Asteroid(double x, double y, double vx, double vy, double radius, int breakUpCount)
    : x(x), y(y), vx(vx), vy(vy), radius(radius), isActive(true), breakUpCount(breakUpCount) {
        int paletteIndex = breakUpCount % colorPalette.size();
        RGBColor selectedColor = colorPalette[paletteIndex];

        colorR = selectedColor.r;
        colorG = selectedColor.g;
        colorB = selectedColor.b;

        creationTime = FsPassedTime();
    }

bool Asteroid::isNew() const {
        long long currentTime = FsPassedTime();
        return (currentTime - creationTime) < 500; // 500 milliseconds
    }

// Update the position of the asteroid
void Asteroid::updatePosition() {
    x += vx;
    y += vy;
}

// Simulate breaking up the asteroid
int Asteroid::breakUp() {
    isActive = false; // For simplicity, just deactivate the asteroid    

    return breakUpCount;
}

// Draw the asteroid
void Asteroid::drawAsteroid() const {
    if (isActive) {
        glColor3f(colorR, colorG, colorB);
        glBegin(GL_LINE_LOOP);
        for(int i = 0; i < 8; i++) {
            float angle = 2 * M_PI * i / 8;
            glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
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
