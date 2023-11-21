#ifndef ASTEROID_MANAGER_HPP
#define ASTEROID_MANAGER_HPP

#include <vector>
#include "asteroid.hpp"
#include <cmath>
#include <random>
#include "fssimplewindow.h"
#include <iostream>
#include <cstdlib>  

class AsteroidManager {
    int difficultyLevel;
    int mapWidth;
    int mapHeight;
    int numAsteroids;
    std::vector<Asteroid> asteroids;
    std::mt19937 gen;
    bool initialized;

public:
    // Default constructor
    AsteroidManager();

    // Initialize function
    void initialize(int level, int width, int height, int num);
    void setDifficulty(int level);
    std::vector<Asteroid> getCurrentAsteroids() const;
    void destroyAsteroid(size_t index);
    void drawAsteroids();
    bool checkCollision(Asteroid& a, Asteroid& b);
    void ballBounce(Asteroid& a, Asteroid& b);
    void updateAsteroids();
    void initializeAsteroid(double posX, double posY, bool isBreakup, int param);
};

#endif // ASTEROID_MANAGER_HPP
