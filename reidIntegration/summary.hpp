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
    int id;  // player id
    int numLevels;  // number of levels
    vector<int> numAsteroidHitLevels;  // number of asteroids hit per level
    vector<int> numBulletShotLevels;  // number of bullets shot per level
    vector<int> timeLevels;  // time spent per level
    vector<int> scoreLevels;  // score per level
    int numAsteroidHitTotal;  // total number of asteroids hit
    int numBulletShotTotal;  // total number of bullets shot
    int timeTotal;  // total time spent
    int scoreTotal;  // total score
    int startTime;  // start time of a level
    int endTime;  // end time of a level

public:
    PlayerStats();  // default constructor
    PlayerStats(int playerId, int numLevels);  // constructor
    int addOneAsteriodHit(int level);  // add one asteroid hit
    int addOneBulletShot(int level);  // add one bullet shot
    int startTimeCounter(int level);  // start time counter
    int saveTimeCounter(int level);  // save time counter
    int computeScoreLevels(int difficulty, int level);  // compute score per level
};

class GameSummary
{
public:
    int difficulty;  // difficulty level
    int numPlayers;  // number of players
    int numLevels;  // number of levels
    int wid;  // window width
    int hei;  // window height
    int vSpace;  // vertical space
    int hSpace;  // horizontal space
    int vOffset;  // vertical offset
    int hOffset;  // horizontal offset
    vector<string> members = {"Nikole Chetty", "Reid Graves" , "Jeremy Kilbride", "Vignesh Menon", "Khai Nguyen", "Pratik Satija", "Anton Yanovich"};  // team members
    vector<string> tasks = {"Integration Design", "Sound Design", "Menu Design", "Ship Design", "Statistics Design", "Background Design", "Asteroid Design"};  // tasks
    string statement = "Thanks for watching!";  // statement

public:
    GameSummary ();
    GameSummary(int numPlayers, int numLevels, int difficulty, int wid, int hei);  // constructor
    ~GameSummary();  // destructor

    // these only show stats on top of the background
    int showStats(PlayerStats stats, int level);  // show statistics
    int showCredit();  // show credit
    int showEndgame(PlayerStats stats);  // show endgame
};
