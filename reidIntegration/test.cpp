#include "summary.hpp"

int main()
{
    int numPlayers = 2;
    int numLevels = 3;
    int difficulty = 1;
    int wid = 800;
    int hei = 600;
    GameSummary gameSummary(numPlayers, numLevels, difficulty, wid, hei);

    // stats does not need to be part of the Ship class
    PlayerStats stats[2] = {PlayerStats(1, numLevels), PlayerStats(2, numLevels)};

    int currentLevel = 0; // 3 levels 0, 1, 2 -> indexes 0, 1, 2
    int displayCredit = 0;
    int gameDone = 0;
    int running = 1;
    FsOpenWindow(50, 50, wid, hei, 1);
    while (true)
    {
        FsPollDevice();
        auto key = FsInkey();
        if (key == FSKEY_ESC)
        {
            break;
        }

        if (key == FSKEY_ENTER)
        {
            // Proceed the game with enter (dummy logic)
            currentLevel++;
            running = 1;
            if (currentLevel >= numLevels)
            {
                gameDone++;
            }
            if (gameDone >= 2)
            {
                displayCredit = 1;
            }
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Playing the game (dummy logic)
        if (currentLevel == 0 && running == 1)
        {
            std::cout << "Playing level 0" << std::endl;
            stats[0].startTimeCounter(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            stats[0].addOneBulletShot(currentLevel);
            stats[0].addOneBulletShot(currentLevel);
            FsSleep(1000);
            stats[0].saveTimeCounter(currentLevel);
            // compute score after each level
            stats[0].computeScoreLevels(difficulty, currentLevel);

            stats[1].startTimeCounter(currentLevel);
            stats[1].addOneAsteriodHit(currentLevel);
            stats[1].addOneBulletShot(currentLevel);
            stats[1].addOneBulletShot(currentLevel);
            FsSleep(1000);
            stats[1].saveTimeCounter(currentLevel);
            stats[1].computeScoreLevels(difficulty, currentLevel);

            running = 0;
        }
        if (currentLevel == 1 && running == 1)
        {
            std::cout << "Playing level 1" << std::endl;
            stats[0].startTimeCounter(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            stats[0].addOneBulletShot(currentLevel);
            FsSleep(1000);
            stats[0].saveTimeCounter(currentLevel);
            stats[0].computeScoreLevels(difficulty, currentLevel);

            stats[1].startTimeCounter(currentLevel);
            stats[1].addOneAsteriodHit(currentLevel);
            stats[1].addOneBulletShot(currentLevel);
            stats[1].addOneBulletShot(currentLevel);
            FsSleep(1000);
            stats[1].saveTimeCounter(currentLevel);
            stats[1].computeScoreLevels(difficulty, currentLevel);

            running = 0;
        }
        if (currentLevel == 2 && running == 1)
        {
            std::cout << "Playing level 2" << std::endl;
            stats[0].startTimeCounter(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            stats[0].addOneAsteriodHit(currentLevel);
            FsSleep(1000);
            stats[0].saveTimeCounter(currentLevel);
            running = 0;
            stats[0].computeScoreLevels(difficulty, currentLevel);
            stats[1].computeScoreLevels(difficulty, currentLevel);
        }

        // After each level is completed, show the stats on the screen
        if (gameDone == 0)
        {
            if (numPlayers == 1)
            {
                gameSummary.showStats(stats[0], currentLevel);
            }
            else
            {
                gameSummary.showStats(stats[0], currentLevel);
                gameSummary.showStats(stats[1], currentLevel);
            }
        }

        // At the end, show the endgame on the screen
        if (gameDone > 0)
        {
            if (displayCredit == 0)
            {
                gameSummary.showEndgame(stats[0]);
                gameSummary.showEndgame(stats[1]);
            }

            if (displayCredit == 1)
                gameSummary.showCredit();
        }

        FsSwapBuffers();
        FsSleep(25);
    }

    return 0;
}
