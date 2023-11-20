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
    return this->startTime;
}

int PlayerStats::saveTimeCounter(int level)
{
    this->endTime = time(NULL);
    this->timeLevels[level] += this->endTime - this->startTime;
    this->timeTotal += this->endTime - this->startTime;
    return this->timeLevels[level];
}

int PlayerStats::computeScore(int difficulty, int level)
{
    this->scoreLevels[level] = (this->numAsteroidHitLevels[level] * 10) - (this->numBulletShotLevels[level] * 5) + (this->timeLevels[level] * 2);
    this->scoreTotal += this->scoreLevels[level];
    return this->scoreLevels[level];
}

Player::Player()
{
    this->stats = PlayerStats(3);
}

Player::~Player()
{
}

GameSummary::GameSummary(int numPlayers, int numLevels, int difficulty)
{
    this->numPlayers = numPlayers;
    this->numLevels = numLevels;
    this->difficulty = difficulty;
}

GameSummary::~GameSummary()
{
}

int GameSummary::showStats(Player player, int level)
{
    cout << "Player " << player.stats.numPlayers << " stats for level " << level << endl;
    cout << "Number of Asteroid Hit: " << player.stats.numAsteroidHitLevels[level] << endl;
    cout << "Number of Bullet Shot: " << player.stats.numBulletShotLevels[level] << endl;
    cout << "Time: " << player.stats.timeLevels[level] << endl;
    cout << "Score: " << player.stats.scoreLevels[level] << endl;
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

int GameSummary::showEndgame(Player player, int level)
{
    cout << "Player " << player.stats.numPlayers << " stats for level " << level << endl;
    cout << "Number of Asteroid Hit: " << player.stats.numAsteroidHitLevels[level] << endl;
    cout << "Number of Bullet Shot: " << player.stats.numBulletShotLevels[level] << endl;
    cout << "Time: " << player.stats.timeLevels[level] << endl;
    cout << "Score: " << player.stats.scoreLevels[level] << endl;
    cout << "Total Number of Asteroid Hit: " << player.stats.numAsteroidHitTotal << endl;
    cout << "Total Number of Bullet Shot: " << player.stats.numBulletShotTotal << endl;
    cout << "Total Time: " << player.stats.timeTotal << endl;
    cout << "Total Score: " << player.stats.scoreTotal << endl;
    return 0;
}
