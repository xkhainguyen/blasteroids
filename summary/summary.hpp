#pragma once

#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "fssimplewindow.h"
#include "ysglfontdata.h"

using namespace std;

class PlayerStats
{
public:
    int id;
    int numLevels;
    vector<int> numAsteroidHitLevels;
    vector<int> numBulletShotLevels;
    vector<int> timeLevels;
    vector<int> scoreLevels;
    int numAsteroidHitTotal;
    int numBulletShotTotal;
    int timeTotal;
    int scoreTotal;
    int startTime;
    int endTime;

public:
    PlayerStats();
    PlayerStats(int playerId, int numLevels);
    int addOneAsteriodHit(int level);
    int addOneBulletShot(int level);
    int startTimeCounter(int level);
    int saveTimeCounter(int level);
    int computeScoreLevels(int difficulty, int level);
};

class GameSummary
{
public:
    int difficulty;
    int numPlayers;
    int numLevels;
    int wid;
    int hei;
    int vSpace;
    int hSpace;
    int vOffset;
    int hOffset;
    vector<string> members = {"Nikole Chetty", "Reid Graves" , "Jeremy Kilbride", "Vignesh Menon", "Khai Nguyen", "Pratik Satija", "Anton Yanovich"};
    vector<string> tasks = {"Integration Design", "Sound Design", "Menu Design", "Ship Design", "Statistics Design", "Background Design", "Asteroid Design"};
    string statement = "Thanks for watching!";

public:
    GameSummary(int numPlayers, int numLevels, int difficulty, int wid, int hei);
    ~GameSummary();
    int showStats(PlayerStats stats, int level);
    int showCredit();
    int showEndgame(PlayerStats stats);
};
