#include "summary.hpp"

PlayerStats::PlayerStats()
{
}

PlayerStats::PlayerStats(int playerId, int numLevels)
{
    this->id = playerId;
    this->numLevels = numLevels;
    this->numAsteroidHitTotal = 0;
    this->numBulletShotTotal = 0;
    this->timeTotal = 0;
    this->scoreTotal = 0;
    this->startTime = 0;
    this->endTime = 0;

    // init with zeros
    for (int i = 0; i < numLevels; i++)
    {
        this->numAsteroidHitLevels.push_back(0);
        this->numBulletShotLevels.push_back(0);
        this->timeLevels.push_back(0);
        this->scoreLevels.push_back(0);
    }
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

int PlayerStats::computeScoreLevels(int difficulty, int level)
{
    this->scoreLevels[level] = (this->numAsteroidHitLevels[level] * 10) - (this->numBulletShotLevels[level] * 5) + (this->timeLevels[level] * 2);
    this->scoreTotal += this->scoreLevels[level];
    return difficulty * this->scoreLevels[level];
}

GameSummary::GameSummary(int numPlayers, int numLevels, int difficulty, int wid, int hei)
{
    this->numPlayers = numPlayers;
    this->numLevels = numLevels;
    this->difficulty = difficulty;
    this->wid = wid;
    this->hei = hei;
    this->vSpace = 40;
    this->hSpace = 0;
    this->vOffset = int(hei / 2);
    this->hOffset = int(wid / 2);
}

GameSummary::GameSummary()
{
}

GameSummary::~GameSummary()
{
}

int GameSummary::showStats(PlayerStats stats, int level)
{
    int _hOffset = int(wid / 4);
    int _vOffset = this->vOffset;
    if (stats.id == 1) {
        glColor3ub(255, 0, 0);
        _vOffset = int(hei / 3) - this->vSpace*2;
    }
    if (stats.id == 2)
    {
        glColor3ub(0, 0, 255);
        _vOffset = int(hei / 3) + 50 + this->vSpace*3;
    }
    
    glRasterPos2i(_hOffset, _vOffset);
    string str = "Player " + to_string(stats.id) + " stats for level " + to_string(level);
    YsGlDrawFontBitmap16x20(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace);
    str = "Number of Asteroid Hit: " + to_string(stats.numAsteroidHitLevels[level]);
    YsGlDrawFontBitmap12x16(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace * 2);
    str = "Number of Bullet Shot: " + to_string(stats.numBulletShotLevels[level]);
    YsGlDrawFontBitmap12x16(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace * 3);
    str = "Time: " + to_string(stats.timeLevels[level]);
    YsGlDrawFontBitmap12x16(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace * 4);
    str = "Score: " + to_string(stats.scoreLevels[level]);
    YsGlDrawFontBitmap12x16(str.c_str());

    return 0;
}

int GameSummary::showCredit()
{
    int _hOffset = int(wid / 4);
    int _vOffset = int(hei / 4) + 30;
    glColor3ub(117, 255, 255);
    glRasterPos2i(_hOffset, _vOffset - 50);
    string str = this->statement;
    YsGlDrawFontBitmap16x20(str.c_str());
    glRasterPos2i(_hOffset, _vOffset);
    str = "Credits";
    YsGlDrawFontBitmap16x20(str.c_str());
    for (int i = 0; i < this->members.size(); i++)
    {
        glRasterPos2i(_hOffset, _vOffset + this->vSpace * (i + 1));
        str = this->members[i] + " - " + this->tasks[i];
        YsGlDrawFontBitmap12x16(str.c_str());
    }
    return 0;
}

int GameSummary::showEndgame(PlayerStats stats)
{    
    int _hOffset = int(wid / 4);
    int _vOffset = this->vOffset;
    if (stats.id == 1) {
        glColor3ub(255, 0, 0);
        _vOffset = int(hei / 3) - this->vSpace*2;
    }
    if (stats.id == 2)
    {
        glColor3ub(0, 0, 255);
        _vOffset = int(hei / 3) + 50 + this->vSpace*3;
    }
    glColor3ub(255,255,255);
    std::cout << __LINE__ << std::endl; 
    glRasterPos2i(300, 400);
    std::string str = "Player " + to_string(stats.id) + " stats for the game";
    std::cout << str << std::endl;
    YsGlDrawFontBitmap16x20(str.c_str());
    std::cout << __LINE__ << std::endl;
    glRasterPos2i(300,400);
    str = "Number of Asteroid Hit: " + to_string(stats.numAsteroidHitTotal);
    YsGlDrawFontBitmap12x16(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace * 2);
    str = "Number of Bullet Shot: " + to_string(stats.numBulletShotTotal);
    YsGlDrawFontBitmap12x16(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace * 3);
    str = "Time: " + to_string(stats.timeTotal);
    YsGlDrawFontBitmap12x16(str.c_str());
    glRasterPos2i(_hOffset, _vOffset + this->vSpace * 4);
    str = "Score: " + to_string(stats.scoreTotal);
    YsGlDrawFontBitmap12x16(str.c_str());
    return 0;
}
