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
    std::vector<int> numAsteroidHitLevels;
    std::vector<int> numBulletShotLevels ;
    std::vector<int> timeLevels;
    std::vector<int> scoreLevels;
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
    GameSummary();
    ~GameSummary();
    void Initialize(int numPlayers, int numLevels, int difficulty);
    int showStats(PlayerStats player, int level, int numPlayer);
    int showCredit();
    void showEndgame(PlayerStats player, int level, int numPlayer);
};

