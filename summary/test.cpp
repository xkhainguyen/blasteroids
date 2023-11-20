#include "PlayerStats.hpp"

int main()
{
    int numPlayers = 2;
    int numLevels = 3;
    int difficulty = 1;
    GameSummary gameSummary(numPlayers, numLevels, difficulty);
    Player player1(0, numLevels);
    Player player2(1, numLevels);

    int currentLevel = 0;
    player1.stats.startTimeCounter(currentLevel);
    // player2.stats.startTimeCounter(currentLevel);

    player1.stats.addOneBulletShot(currentLevel);
    player1.stats.addOneBulletShot(currentLevel);
    player1.stats.addOneAsteriodHit(currentLevel);

    player1.stats.saveTimeCounter(currentLevel);
    std::cout << player1.stats.numAsteroidHitLevels[currentLevel] << std::endl;
    // player1.stats.computeScore(difficulty, currentLevel);

    // gameSummary.showStats(player1, currentLevel);   

    // currentLevel = 1;
    // player1.stats.startTimeCounter(currentLevel);
    // player1.stats.addOneBulletShot(currentLevel);
    // player1.stats.addOneAsteriodHit(currentLevel);
    // player1.stats.saveTimeCounter(currentLevel);
    // player1.stats.computeScore(difficulty, currentLevel);

    // gameSummary.showStats(player1, currentLevel);
    
    return 0;
}
