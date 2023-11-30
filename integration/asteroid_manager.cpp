#include "asteroid_manager.hpp"
#include <random>
#include <vector>


AsteroidManager::AsteroidManager() : gen(std::random_device()()), initialized(false) {
    // Constructor implementation
}

void AsteroidManager::initialize(int level, int width, int height, int num) {
    difficultyLevel = level;
    mapWidth = width;
    mapHeight = height;
    numAsteroids = num;

    // Clear existing asteroids and reinitialize
    asteroids.clear();
    for (int i = 0; i < numAsteroids; ++i) {
        initializeAsteroid(0.0, 0.0, false, 0);
    }

    // Initialize asteroids
    setDifficulty(difficultyLevel);

    initialized = true; // Mark as initialized
}


// Set the difficulty level
void AsteroidManager::setDifficulty(int level) {
    difficultyLevel = level;

    // Clear existing asteroids
    asteroids.clear();

    // Initialize new asteroids
    for (int i = 0; i < numAsteroids; i++) {
        initializeAsteroid(0.0, 0.0, false, 0);
    }
}

void AsteroidManager::initializeAsteroid(double posX = 0, double posY = 0, bool isBreakup = false, int param = 0)
{
    std::uniform_real_distribution<> dis(-10.0 * difficultyLevel, 10.0 * difficultyLevel);
    std::uniform_real_distribution<> disPos(0, mapHeight);
    std::uniform_real_distribution<> disRadius(10, 30);

    // Initialize new asteroids
    double velocityX = dis(gen);
    double velocityY = dis(gen);
    double x = (rand() % 2 == 0) ? 0 : mapWidth; // Half the asteroids start on the left edge, half on the right
    double y = disPos(gen);
    double radius = disRadius(gen);
    if (!isBreakup)
        asteroids.push_back(Asteroid(x, y, velocityX, velocityY, radius, 0));
    else{
        radius /= difficultyLevel;
        asteroids.push_back(Asteroid(posX, posY, velocityX, velocityY, radius, param));
    }
}

// Get the current active asteroids
std::vector<Asteroid> AsteroidManager::getCurrentAsteroids() const {
    return asteroids;
}

// Destroy an asteroid at the given index
void AsteroidManager::destroyAsteroid(size_t index) {
    // Logic to destroy or break up an asteroid
    if (index < asteroids.size()) {
        // Break up the asteroid and get the number of times it has broken up
        
        int breakups = asteroids[index].breakUp();
        std::pair<double, double> pos = asteroids[index].getPosition();
        double posX = pos.first;
        double posY = pos.second;

        // Remove the original asteroid
        asteroids.erase(asteroids.begin() + index);

        // If the asteroid has not broken up difficultyLevel times, create smaller asteroids
        if (breakups <= difficultyLevel) {
            breakups++;
            for (int i = 1; i < difficultyLevel; i++) {
                initializeAsteroid(posX, posY, true, breakups);
            }
        }
    }
    else {
        std::cout << "Invalid destroyAsteroid index: " << index << std::endl;
    }
}

// Draw all active asteroids
void AsteroidManager::drawAsteroids() {
    for (auto& asteroid : asteroids) {
        if (asteroid.getState()) {
            asteroid.drawAsteroid();
        }
    }
}

// Check if two asteroids are colliding
bool AsteroidManager::checkCollision(Asteroid& a, Asteroid& b) {
    double dx = b.x - a.x;
    double dy = b.y - a.y;
    double distance = std::sqrt(dx * dx + dy * dy);
    return distance < (a.radius + b.radius);
}

// Handle the bouncing of two colliding asteroids
void AsteroidManager::ballBounce(Asteroid& a, Asteroid& b) {
    double nx = b.x - a.x;
    double ny = b.y - a.y;
    double distance = std::sqrt(nx * nx + ny * ny);

    if (distance != 0) {
        nx /= distance;
        ny /= distance;

        double k1 = a.vx * nx + a.vy * ny;
        double k2 = b.vx * nx + b.vy * ny;

        a.vx = a.vx + nx * (k2 - k1);
        a.vy = a.vy + ny * (k2 - k1);
        b.vx = b.vx + nx * (k1 - k2);
        b.vy = b.vy + ny * (k1 - k2);
    }
}

// Update the positions of all asteroids and check for collisions
void AsteroidManager::updateAsteroids() {
    for (size_t i = 0; i < asteroids.size(); i++) {
        asteroids[i].updatePosition();

        // Wrap the asteroid around the screen
        if (asteroids[i].x < 0) asteroids[i].x = mapWidth;
        else if (asteroids[i].x > mapWidth) asteroids[i].x = 0;

        if (asteroids[i].y < 0) asteroids[i].y = mapHeight;
        else if (asteroids[i].y > mapHeight) asteroids[i].y = 0;

        for (size_t j = i + 1; j < asteroids.size(); j++) {
            if (checkCollision(asteroids[i], asteroids[j])) {
                ballBounce(asteroids[i], asteroids[j]);
            }
        }
    }
}
