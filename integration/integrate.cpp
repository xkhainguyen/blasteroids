
#include <iostream>
#include <vector>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "menu.h"
#include "background.h"
#include "ship.h"
#include "asteroid_manager.hpp"
#include <cstdlib>

// Mock implementations of your subclasses

// class Ship {
// public:
//     bool state = true;

//     void initialize() {
//         std::cout << "Ship initialized" << std::endl;
//     }

//     void render() {
//         std::cout << "Ship rendered" << std::endl;
//     }

//     void updateShip() {
//         std::cout << "Ship updated" << std::endl;
//     }

//     void updateMissiles() {
//         std::cout << "Missiles updated" << std::endl;
//     }
// };

class Sound {
public:
    void initialize() {
        // std::cout << "Sound initialized" << std::endl;
    }

    void render() {
        // std::cout << "Sound rendered" << std::endl;
    }

    void endGame() {
        // std::cout << "Sound end game" << std::endl;
    }
};

class Summary {
public:
    void showEndGame() {
        // std::cout << "End game summary shown" << std::endl;
    }
};



class Game {
public:
    GameMenu menu;
    // Ship ship;
    Sound sound;
    Summary summary;    
    AsteroidManager manager;

    bool isGameOver;
    int x1 = 200, y1 = 550, x2 = 600, y2 = 550;
	int friendlyFire = 0;
	int windowWidth = 800, windowHeight = 600;
	Ship ships[2] = { Ship(x1, y1, windowWidth, windowHeight, 1), Ship(x2, y2, windowWidth, windowHeight, 2) };


    Game() {
        // Initialize the game state
        isGameOver = false;
        FsOpenWindow(50,50,800,600,1);
    }



    void start() {
        // Display menu and get player choices
        displayMenu();
        // Initialize game components based on player choices
        initializeGame();
        // Main game loop
        std::cout << "Game starting!!" << std::endl;

        while (!isGameOver) {
            FsPollDevice();
            if (FsGetKeyState(FSKEY_ESC)) {
                break;
            }
            // Update game state
            updateGame();

            // Render game frame
            renderFrame();

            // Check for game over conditions
            isGameOver = checkGameOver();
        }
        // Display end game summary and credits
        while (!FsGetKeyState(FSKEY_ESC)) {
            FsPollDevice();
            displayEndGameSummary();
        }

    }

private:
    void displayMenu() {
        
        menu.SetButtons();
        for(;;)
        {
            int menu_sel=menu.RunOneStep();
            if(GameMenu::BMENU_Start==menu_sel)
            {
                if (true==menu.isMultiplayer)
                {
                    std::cout<<"the game has started, difficulty is:"<<menu.difficulty<< " there are two players" << std::endl;
                }
                else
                {
                    std::cout<<"the game has started, difficulty is:"<<menu.difficulty<< " there is one player" << std::endl;
                }
                break;
            }
            else if (GameMenu::BMENU_QUIT==menu_sel)
            {
                std::cout<<"the user has exited the game" << std::endl;
                break;
            }
        }
    }



    void initializeGame() {
        // Initialize ship, asteroids, sounds, and background

        // Initialize asteriods 
        int difficulty_level = convertDifficultyCharToInt(menu.difficulty);
        int asteroid_count = 2;
        manager.initialize(difficulty_level, 800, 600, asteroid_count);
        std::cout << "Asteroids: " << manager.getCurrentAsteroids().size() << std::endl;

        // ship.initialize();
        sound.initialize();
    }

    int convertDifficultyCharToInt(char difficultyChar) {
        switch (difficultyChar) {
            case 'e':
                return 1;
            case 'm':
                return 2;
            case 'h':
                return 3;
            default:
                std::cerr << "Invalid difficulty character" << std::endl;
                return 1; // or any other default/error value
        }
    }


    void renderFrame() {
        // Render background, ship, asteroids
		FsPollDevice();
		auto key = FsInkey();

		switch (key)
		{
		case FSKEY_LEFT:
			ships[0].moveShipLeft();
			break;
		case FSKEY_RIGHT:
			ships[0].moveShipRight();
			break;
		case FSKEY_UP:
			ships[0].moveShipUp();
			break;
		case FSKEY_DOWN:
			ships[0].moveShipDown();
			break;
		case FSKEY_SPACE:
			ships[0].TriggerMissile();
			break;

		case FSKEY_A:
			ships[1].moveShipLeft();
			break;
		case FSKEY_D:
			ships[1].moveShipRight();
			break;
		case FSKEY_W:
			ships[1].moveShipUp();
			break;
		case FSKEY_S:
			ships[1].moveShipDown();
			break;
		case FSKEY_Q:
			ships[1].TriggerMissile();
			break;
		}

		friendlyFire += ships[0].CheckCollisionWithOtherShipMissiles(ships[1]);
		friendlyFire += ships[1].CheckCollisionWithOtherShipMissiles(ships[0]);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawBackground();

		ships[0].DrawPlayer();
		ships[1].DrawPlayer();

		for (auto& ship : ships) {
			ship.ShootMissile();
		}

        manager.drawAsteroids();
        
        FsSwapBuffers();
        FsSleep(25);
    }


    void updateGame() {
        // Update asteroids
        manager.updateAsteroids();

        // Update ship --- future, currently in renderFrame


        /////////////////////// Check for collisions //////////////////////
        // ship-asteroid, asteroid-missle, missle-ship
        
        size_t asteriod_counter = 0;
        for (auto& aster : manager.getCurrentAsteroids()) {
            for (auto& ship : ships) {            
                if (checkCollision(ship.xCoord, ship.yCoord, 15, aster.x, aster.y, aster.radius)){
                    ship.isAlive = false;
                }
                else {
                    for (auto& missile : ship.missiles) {  
                        if (missile.isActive){
                            if (checkCollision(missile.xCoord, missile.yCoord, 2, aster.x, aster.y, aster.radius)){
                                missile.isActive = false;
                                manager.destroyAsteroid(asteriod_counter);
                            };
                        }
                    }
                }
            }
            asteriod_counter = asteriod_counter +1;

		}

    }

    bool checkCollision(int aX, int aY, int aRad, int bX, int bY, int bRad) {
    // Check if two objects are colliding
        double dx = bX - aX;
        double dy = bY - aY;
        double distance = std::sqrt(dx * dx + dy * dy);
        return distance < (aRad + bRad);
    }

   bool checkGameOver() {
        // Check if game over conditions are met
        // Ship dead :(
        // need to adjest to check for multiple ships
        if (!ships[0].isAlive & !ships[1].isAlive) {
            std::cout<<"Game over!! The ship died!!" << std::endl;
            return true;
        }

        // Asteroids 
        size_t noAsteroids = 0;
        if (noAsteroids != manager.getCurrentAsteroids().size()) {
            return false;
        }
        else {
            std::cout<< "Game over!! All the asteriods are gone!!!" << std::endl;
            return true;
        }

        return false;

    }

void displayEndGameSummary() {
    // Display summary statistics and credits
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawBackground();
    summary.showEndGame();
    sound.endGame();
    FsSwapBuffers();
    FsSleep(25);
    // std::cout<< "Print game end summary" << std::endl;
    }

};


// Test the Game class
int main() {
    Game game;
    game.start();
    return 0;
}
