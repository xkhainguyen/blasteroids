#ifndef ASTEROID_HPP
#define ASTEROID_HPP

#include <string>
#include <cmath>
#include "fssimplewindow.h"
#include <utility>
#include <math.h>
#include <cstdlib>
#include <vector>
#include <chrono>

class Asteroid {
public:
    double x, y; // Position
    double vx, vy; // Velocity
    double radius;
    bool isActive;
    int breakUpCount = 0;
    //long long creationTime;
    std::chrono::steady_clock::time_point creationTime;
    //std::string appearance; // Representation of the asteroid's visual appearance

    Asteroid(double x, double y, double vx, double vy, double radius, int breakUpCount);
    void updatePosition();
    int breakUp();
    void drawAsteroid() const;
    bool getState() const;
    std::string toString() const;
    std::pair<double,double> getPosition() const;

    bool isNew() const;
private:
    float colorR, colorG, colorB;
};

#endif // ASTEROID_HPP
