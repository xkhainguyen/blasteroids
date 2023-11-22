#include "PlayerStats.hpp"

PlayerStats::PlayerStats()
{
}

PlayerStats::PlayerStats(int numLevels)
{
    this->numLevels = numLevels;
    this->numPlayers = 0;
    this->numAsteroidHitLevels = new int[numLevels];
    this->numBulletShotLevels = new int[numLevels];
    this->timeLevels = new int[numLevels];
    this->scoreLevels = new int[numLevels];
    this->numAsteroidHitTotal = 0;
    this->numBulletShotTotal = 0;
    this->timeTotal = 0;
    this->scoreTotal = 0;
    this->startTime = 0;
    this->endTime = 0;

    // init with zeros
    for (int i = 0; i < numLevels; i++)
    {
        this->numAsteroidHitLevels[i] = 0;
        this->numBulletShotLevels[i] = 0;
        this->timeLevels[i] = 0;
        this->scoreLevels[i] = 0;
    }
}

PlayerStats::~PlayerStats()
{
    delete[] this->numAsteroidHitLevels;
    delete[] this->numBulletShotLevels;
    delete[] this->timeLevels;
    delete[] this->scoreLevels;
}

int PlayerStats::addOneAsteriodHit(int level)
{
    this->numAsteroidHitLevels[level]++;
    this->numAsteroidHitTotal++;
    return this->numAsteroidHitLevels[level];
}

int PlayerStats::addOneBulletShot(int level)
{
    this->numBulletShotLevels[level]++;
    this->numBulletShotTotal++;
    return this->numBulletShotLevels[level];
}

int PlayerStats::startTimeCounter(int level)
{
    this->startTime = time(NULL);
    // cout << "Start time" << startTime << endl;
    return this->startTime;

}

int PlayerStats::saveTimeCounter(int level)
{
    // cout << "Stopped timer for level " << level << endl;
    this->endTime = time(NULL);
    this->timeLevels[level] += this->endTime - this->startTime;
    // cout << "TimeLevels " << timeLevels[level] << endl;
    this->timeTotal += this->endTime - this->startTime;
    // cout << "Saved time: " << timeTotal << endl;
    return this->endTime - this->startTime;
    
}

int PlayerStats::computeScore(int difficulty, int level)
{
    this->scoreLevels[level] = (this->numAsteroidHitLevels[level] * 10) - (this->numBulletShotLevels[level] * 5) + (this->timeLevels[level] * 2);
    this->scoreTotal += this->scoreLevels[level];
    return this->scoreLevels[level];
}



GameSummary::GameSummary()
{
}

GameSummary::~GameSummary()
{
}

void GameSummary::Initialize(int numPlayers, int numLevels, int difficulty)
{
    this->numPlayers = numPlayers;
    this->numLevels = numLevels;
    this->difficulty = difficulty;
}

int GameSummary::showStats(PlayerStats player, int level, int numPlayer)
{
    cout << "Player " << numPlayer << " stats for level " << level << endl;
    cout << "Number of Asteroid Hit: " << player.numAsteroidHitLevels[level] << endl;
    cout << "Number of Bullet Shot: " << player.numBulletShotLevels[level] << endl;
    cout << "Time: " << player.timeLevels[level] << endl;
    cout << "Score: " << player.scoreLevels[level] << endl;
    return 0;
}

int GameSummary::showCredit()
{
    cout << "Game Summary" << endl;
    cout << "Number of Players: " << this->numPlayers << endl;
    cout << "Number of Levels: " << this->numLevels << endl;
    cout << "Difficulty: " << this->difficulty << endl;
    return 0;
}

int GameSummary::showEndgame(PlayerStats player, int level, int numPlayer)
{
    cout << "Player " << numPlayer << " stats for level " << level << endl;
    cout << "Number of Asteroid Hit: " << player.numAsteroidHitLevels[level] << endl;
    cout << "Number of Bullet Shot: " << player.numBulletShotLevels[level] << endl;
    cout << "Time: " << player.timeLevels[level] << endl;
    cout << "Score: " << player.scoreLevels[level] << endl;
    cout << "Total Number of Asteroid Hit: " << player.numAsteroidHitTotal << endl;
    cout << "Total Number of Bullet Shot: " << player.numBulletShotTotal << endl;
    cout << "Total Time: " << player.timeTotal << endl;
    cout << "Total Score: " << player.scoreTotal << endl;
    return 0;
}
