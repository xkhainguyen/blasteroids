
#include <iostream>
#include <vector>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "mmlplayer.h"
#include "yssimplesound.h"
#include "menu.h"
#include "background.h"
#include "ship.h"
#include "asteroid_manager.hpp"
#include "SoundManager.h"
#include "PlayerStats.hpp"
#include <cstdlib>



class Game {
public:
    bool isGameOver;
    int currentLevel = 1;
    int x1 = 200, y1 = 550, x2 = 600, y2 = 550;
	int friendlyFire = 0;
	int windowWidth = 800, windowHeight = 600;
    int numPlayers;
    int difficulty_level = 1;


    GameMenu menu;
    SoundManager soundManager;   
    AsteroidManager manager;
    GameSummary gameSummary;
    

    // TODO: Two ships are currently hardcoded - needs to be updated 
	Ship ships[2] = { Ship(x1, y1, windowWidth, windowHeight, 1), Ship(x2, y2, windowWidth, windowHeight, 2) };
    PlayerStats stats[2] = { PlayerStats(3), PlayerStats(3)};


    Game() {
        // Initialize the game state
        isGameOver = false;
        FsOpenWindow(50,50,800,600,1);
    }



    void run() {
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
            if (FsGetKeyState(FSKEY_P)) {
                std::cout << "Game paused" << std::endl;
                FsPollDevice();
                while (!FsGetKeyState(FSKEY_O)) {
                    FsPollDevice();
                }
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
        // Initialize ship, asteroids, & sounds

        // Initialize asteriods 
        difficulty_level = convertDifficultyCharToInt(menu.difficulty);
        int asteroid_count = 2;
        manager.initialize(difficulty_level, 800, 600, asteroid_count);
        std::cout << "Asteroids: " << manager.getCurrentAsteroids().size() << std::endl;

        
        if (true==menu.isMultiplayer){
            numPlayers = 2;
        }
        else {
            numPlayers = 1;
        }

        // Initialize ship
        if (numPlayers == 2) {
			ships[0] = Ship(x1, y1, windowWidth, windowHeight, 1);
			ships[1] = Ship(x2, y2, windowWidth, windowHeight, 2);
		}
		else if (numPlayers == 1) {
			ships[0] = Ship(400, 550, windowWidth, windowHeight, 1);
			ships[1].isAlive = false;
		}


        // Initialize sound
        soundManager.Initialize();
        soundManager.player.Start();
        soundManager.PlayMusic();
        
        gameSummary.Initialize(numPlayers, 3, difficulty_level);
        
        for (auto& stat : stats) {
            stat.startTimeCounter(currentLevel);
        }


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
		
		// friendlyFire += ships[0].CheckCollisionWithOtherShipMissiles(ships[1]);
		// friendlyFire += ships[1].CheckCollisionWithOtherShipMissiles(ships[0]);
        FsSwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        DrawBackground();
        
        ships[0].draw();
        ships[1].draw();
		// ships[0].DrawPlayer();
		// ships[1].DrawPlayer();

		// for (auto& ship : ships) {
		// 	ship.ShootMissile();
		// }

        // ASTEROIDS
        manager.drawAsteroids();
    

        // SOUND, New note: UpdateStream not needed anymore
        // soundManager.UpdateStream();

        // FsSwapBuffers();
        FsSleep(25);

    }


    void updateGame() {
        // Update asteroids
        manager.updateAsteroids();

        // TODO: Update ship ----- currently in renderFrame
        FsPollDevice();
		auto key = FsInkey();

        if (key == FSKEY_ESC) 
        {
			return;
		}
		ships[0].update(key, ships[1]);
		ships[1].update(key, ships[0]);

        // SHIP 
		switch (key)
		{
		case FSKEY_UP:
			// ships[0].moveShipUp();
            soundManager.PlayThrust();
			break;
		case FSKEY_SPACE:
			// ships[0].TriggerMissile();
            soundManager.PlayShoot();
            stats[0].addOneBulletShot(currentLevel);
			break;
		case FSKEY_W:
			// ships[1].moveShipUp();
            soundManager.PlayThrust();
			break;
		case FSKEY_Q:
			// ships[1].TriggerMissile();
            soundManager.PlayShoot();
            stats[1].addOneBulletShot(currentLevel);
			break;
		}


        /////////////////////// Check for collisions //////////////////////
        // ship-asteroid, asteroid-missle, missle-ship
        
        size_t asteriod_counter = 0;
        
        for (auto& aster : manager.getCurrentAsteroids()) {
            int current_ship = 0;
            for (auto& ship : ships) {            
                if (checkCollision(ship.xCoord, ship.yCoord, 15, aster.x, aster.y, aster.radius)){
                    if (ship.isAlive){
                        ship.isAlive = false;
                        soundManager.PlayExplosion();
                        stats[current_ship].saveTimeCounter(currentLevel);
                    }
                    
                }
                else {
                    for (auto& missile : ship.missiles) {  
                        if (missile.isActive){
                            if (checkCollision(missile.xCoord, missile.yCoord, 2, aster.x, aster.y, aster.radius)){
                                missile.isActive = false;
                                manager.destroyAsteroid(asteriod_counter);
                                soundManager.PlayTink();
                                stats[current_ship].addOneAsteriodHit(currentLevel);
                            };
                        }
                    }
                }
                current_ship = current_ship+1;
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
        // need to adjest to check for multiple ship

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
    for (int player = 0; player < numPlayers; ++player) {
        if (ships[player].isAlive) {
            stats[player].saveTimeCounter(currentLevel);
        }
        gameSummary.showStats(stats[player], currentLevel, player);   
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawBackground();

    glColor3ub(255, 0, 255);
    glRasterPos2i(100,100);
    YsGlDrawFontBitmap12x16("Game over");

    FsSwapBuffers();
    FsSleep(25);
    // std::cout<< "Print game end summary" << std::endl;
    }

};


// Test the Game class
int main() {
    Game game;
    game.run();
    return 0;
}
