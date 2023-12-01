
#include <iostream>
#include <vector>
#include <iostream>
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include "menu.h"
#include "background.h"
#include "ship.h"
#include "asteroid_manager.hpp"
#include "SoundManager.h"
#include "summary.hpp"
#include <cstdlib>

// Windows compiler:
// cl /EHsc integrate.cpp menu.cpp fssimplewindow.cpp ysglfontdata.c yssimplesound.cpp mmlplayer.cpp 
// background.cpp asteroid.cpp asteroid_manager.cpp ship.cpp SoundManager.cpp PlayerStats.cpp



class Game {
public:
    bool isGameOver;
    int currentLevel = 1;
    int x1 = 200, y1 = 550, x2 = 600, y2 = 550;
	int friendlyFire = 0;
	int windowWidth = 800, windowHeight = 600;
    int numPlayers;
    int difficultySetting = 1;
    int maxDifficulty = 3;
    int maxLevel = 5;
    int asteriods_per_level[6] = {1, 2, 4, 6, 8, 10};



    GameMenu menu;
    SoundManager soundManager;   
    AsteroidManager manager;
    GameSummary gameSummary;
    Background background;
	Ship ships[2] = { Ship(x1, y1, windowWidth, windowHeight, 1), Ship(x2, y2, windowWidth, windowHeight, 2) };
    PlayerStats stats[2] = { PlayerStats(1,maxLevel), PlayerStats(2,maxLevel)};


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
                    if (FsGetKeyState(FSKEY_ESC)) {
                        break;
            }
                }
            }
            // Update game state
            updateGame();

            // Render game frame
            renderFrame();

            // Check for level complete conditions
            checkLevelUp();

            // Check for game over conditions
            isGameOver = checkGameOver();
        }

        // Display end game summary and credits
        std::cout << "About to display end summary" << std::endl;
        displayEndGameSummary();
        for (;;) {
            FsPollDevice();
            auto key=FsInkey();
            if (key == FSKEY_ESC)
            {
                break;
            }
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
                    std::cout<<"The game has started, difficulty is: "<<menu.difficulty<< ", there are two players" << std::endl;
                }
                else
                {
                    std::cout<<"The game has started, difficulty is: "<<menu.difficulty<< ", there is one player" << std::endl;
                }
                break;
            }
            else if (GameMenu::BMENU_QUIT==menu_sel)
            {
                std::cout<<"Game exited" << std::endl;
                break;
            }
        }
    }


    void checkDifficulty() {
        if (difficultySetting < 1 || difficultySetting > maxDifficulty) {
            difficultySetting = 1;
        }
    }



    void initializeGame() {
        // Initialize ship, asteroids, & sounds

        // Initialize asteriods 
        difficultySetting = menu.difficulty;
        checkDifficulty();
        manager.initialize(difficultySetting, 800, 600, asteriods_per_level[currentLevel]);
        background.InitializeStars(200);
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

        
        gameSummary.numPlayers = numPlayers;
        gameSummary.numLevels = 3;
        gameSummary.difficulty = difficultySetting;
        
        for (auto& stat : stats) {
            stat.startTimeCounter(currentLevel);
        }

        std::cout<<"Game initialization complete" << std::endl;
    }



    void renderFrame() {
        // Render background, ship, asteroids
        FsSwapBuffers();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        background.DrawBackground();
        
        ships[0].draw();
        ships[1].draw();

        manager.drawAsteroids();
    
        FsSleep(25);
    }


    void updateGame() {
        // Update asteroids
        manager.updateAsteroids();

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
        // ship-asteroid and asteroid-missle
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
                                soundManager.PlayExplosion();
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
        if (!ships[0].isAlive & !ships[1].isAlive) {
            std::cout<<"Game over!! The ship died!!" << std::endl;
            return true;
        }

        // All levels complete
        if (currentLevel == maxLevel){
            std::cout<<"Game over!! All levels completed!" << std::endl;
            return true;

        }
        
        return false;

    }

    void checkLevelUp() {
        // Check if any asteroids are left
        size_t noAsteroids = 0;
        if (noAsteroids == manager.getCurrentAsteroids().size()) {
            std::cout<< "Level up!! All the asteriods are gone!!!" << std::endl;
            currentLevel = currentLevel + 1;
            InitializeNextLevel();
        }

    }

    void InitializeNextLevel() {

        for (int player = 0; player < numPlayers; ++player) {
            if (ships[player].isAlive) {
                // Need summary stats here 
                // stats[player].saveTimeCounter(currentLevel-1);
                // gameSummary.showStats(stats[player], currentLevel-1, player); 
                // stats[player].startTimeCounter(currentLevel);
            }

        }

        manager.initialize(difficultySetting, 800, 600, asteriods_per_level[currentLevel]);
        std::cout<< "New asteriods intialized. #: " << manager.getCurrentAsteroids().size() << std::endl;
        std::cout << "Current level: " << currentLevel << std::endl;

        // Deactivate all missles 
        for (auto& ship : ships) {   
            for (auto& missile : ship.missiles) {  
                if (missile.isActive){
                    missile.isActive = false;
                    };
                }
            }
        
        // std::cout<< "Ship missles reloaded" << std::endl;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        background.DrawBackground();

        glColor3ub(117, 255, 255);
        glRasterPos2i(300,100);
        YsGlDrawFontBitmap12x16("Level Complete");
        glRasterPos2i(200,200);
        YsGlDrawFontBitmap12x16("Press enter to start new level");

        FsSwapBuffers();
        FsSleep(25);

        // Display mid game summary
        while (!FsGetKeyState(FSKEY_ESC)) {
            FsPollDevice();
            if (FsGetKeyState(FSKEY_ENTER)) {
                break;
            }
        }
        
    }

    void displayEndGameSummary() {
        // Display summary statistics and credits
        for (int player = 0; player < numPlayers + 1; ++player) {
        std::cout << __LINE__ << std::endl;
            if (ships[player].isAlive) {
                stats[player].saveTimeCounter(currentLevel);
            }
            gameSummary.showEndgame(stats[player]);   
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        background.DrawBackground();

        glColor3ub(255, 0, 255);
        glRasterPos2i(300,100);
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
