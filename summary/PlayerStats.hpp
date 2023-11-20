#pragma once

#include <time.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class PlayerStats
{
public:
    int numPlayers;
    int numLevels;
    int *numAsteroidHitLevels;
    int *numBulletShotLevels;
    int *timeLevels;
    int *scoreLevels;
    int numAsteroidHitTotal;
    int numBulletShotTotal;
    int timeTotal;
    int scoreTotal;
    int startTime;
    int endTime;

public:
    PlayerStats();
    PlayerStats(int numLevels);
    ~PlayerStats();
    int addOneAsteriodHit(int level);
    int addOneBulletShot(int level);
    int startTimeCounter(int level);
    int saveTimeCounter(int level);
    int computeScore(int difficulty, int level);
};

// Dummy player class, should be ship class later
class Player
{
public:
    int id;
    PlayerStats stats;

public:
    Player();
    Player(int id, int numLevels);
    ~Player();
};

class GameSummary
{
public:
    int difficulty;
    int numPlayers;
    int numLevels;
    vector<string> members;
    vector<string> tasks;
    string statement = "Thanks for watching";

public:
    GameSummary(int numPlayers, int numLevels, int difficulty);
    ~GameSummary();
    int showStats(Player player, int level);
    int showCredit();
    int showEndgame(Player player, int level);
};
