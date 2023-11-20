#include "PlayerStats.hpp"

int main()
{
    int numPlayers = 2;
    int numLevels = 3;
    int difficulty = 1;
    GameSummary gameSummary(numPlayers, numLevels, difficulty);
    Player player1;
    Player player2;

    int currentLevel = 1;
    player1.stats.startTimeCounter(currentLevel);
    player2.stats.startTimeCounter(currentLevel);

    player1.stats.addOneBulletShot(currentLevel);
    player1.stats.addOneBulletShot(currentLevel);
    player1.stats.addOneAsteriodHit(currentLevel);

    player1.stats.saveTimeCounter(currentLevel);
    player1.stats.computeScore(difficulty, currentLevel);

    gameSummary.showStats(player1, currentLevel);   

    currentLevel = 2;
    player1.stats.startTimeCounter(currentLevel);
    player1.stats.addOneBulletShot(currentLevel);
    player1.stats.addOneAsteriodHit(currentLevel);
    player1.stats.saveTimeCounter(currentLevel);
    player1.stats.computeScore(difficulty, currentLevel);

    gameSummary.showStats(player1, currentLevel);
    
    return 0;
}
