#include <vector>
#include <iostream>
using namespace std;

// Mock implementations of your subclasses

class Menu {
public:
    int DifficultySelection = 1;
    bool ModeSelection = false;

    void draw() {
        cout << "Menu drawn" << endl;
    }

    void wait() {
        cout << "Waiting for user input" << endl;
    }
};

class Ship {
public:
    bool state = true;

    void initialize() {
        cout << "Ship initialized" << endl;
    }

    void render() {
        cout << "Ship rendered" << endl;
    }

    void updateShip() {
        cout << "Ship updated" << endl;
    }

    void updateMissles() {
        cout << "Missiles updated" << endl;
    }
};

class Asteroid {
public:
    bool state = true;

    void initialize() {
        cout << "Asteroid initialized" << endl;
    }

    void render() {
        cout << "Asteroid rendered" << endl;
    }

    void update() {
        cout << "Asteroid updated" << endl;
    }

    void checkCollisions() {
        cout << "Checking asteroid collisions" << endl;
    }
};

class Sound {
public:
    void initialize() {
        cout << "Sound initialized" << endl;
    }

    void render() {
        cout << "Sound rendered" << endl;
    }

    void endGame() {
        cout << "Sound end game" << endl;
    }
};

class Background {
public:
    void initialize() {
        cout << "Background initialized" << endl;
    }

    void render() {
        cout << "Background rendered" << endl;
    }

    void endGame() {
        cout << "Background end game" << endl;
    }
};

class Summary {
public:
    void showEndGame() {
        cout << "End game summary shown" << endl;
    }
};



class Game {
public:
    Menu menu;
    Ship ship;
    vector<Asteroid> asteroids;
    Sound sound;
    Background background;
    Summary summary;
    bool isGameOver;
    bool isMultiplayer;
    int difficultyLevel;

    Game() {
        // Initialize the game state
        isGameOver = false;
        isMultiplayer = false;
        difficultyLevel = 1; 
    }

    void start() {
        // Display menu and get player choices
        displayMenu();
        // Initialize game components based on player choices
        initializeGame();
        // Main game loop
        while (!isGameOver) {
            // Render game frame
            renderFrame();
            // Update game state
            updateGame();
            // Check for game over conditions
            isGameOver = checkGameOver();
        }
        // Display end game summary and credits
        displayEndGameSummary();
    }

private:
    void displayMenu() {
        // Display menu 
        menu.draw();
        // Wait for button press to continue
        menu.wait();
        // Get player choices
        difficultyLevel = menu.DifficultySelection;//this is an enum variable not a function
        isMultiplayer = menu.ModeSelection;//this is a bool variable 
    }

    void initializeGame() {
        // Initialize ship, asteroids, sounds, and background
        ship.initialize();
        initializeAsteroids(); 
        sound.initialize();
        background.initialize();
    }

    void initializeAsteroids() {
        int numberOfAsteroids = 5; // Example number, change as needed
        for (int i = 0; i < numberOfAsteroids; ++i) {
            Asteroid asteroid;
            asteroids.push_back(asteroid);
        }
    }

    void renderFrame() {
        // Render background, ship, asteroids
        background.render();
        ship.render();
        for (Asteroid& asteroid : asteroids) {
            asteroid.render();
        }
        sound.render();
    }

    void updateGame() {
        // Update ship & asteroids
        ship.updateShip();
        ship.updateMissles();
        for (Asteroid& asteroid : asteroids) {
            asteroid.update();
        }
        // Check for collisions
        // ship-ship, ship-asteroid, asteroid-asteriod, asteroid-missle, missle-ship
        for (Asteroid& asteroid : asteroids) {
            asteroid.checkCollisions();
        }        
    }

   bool checkGameOver() {
        // Check if game over conditions are met
        // Ship dead :(

        // need to adjest to check for multiple ships
        if (!ship.state) {
            return true;
        }

        // Asteroids still left 
        for (Asteroid& asteroid : asteroids) {
            if (asteroid .state) {
                return false;
            }
            else {
                return true;
            }
        }
    }

void displayEndGameSummary() {
    // Display summary statistics and credits
    summary.showEndGame();
    background.endGame();
    sound.endGame();
    }

};


// Test the Game class
int main() {
    Game game;
    game.start();
    return 0;
}
