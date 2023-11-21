#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "yssimplesound.h"
#include "mmlplayer.h"

class SoundManager
{
public:
    MMLSegmentPlayer mmlplayer;
    YsSoundPlayer player;
    YsSoundPlayer::SoundData blaster;
    YsSoundPlayer::SoundData explosion;
    YsSoundPlayer::SoundData rocketThrust;
    YsSoundPlayer::SoundData tink;
    YsSoundPlayer::Stream stream;
    YsSoundPlayer::SoundData nextWave;

    void Initialize(void);
    void UpdateStream(void);
    void PlaySound(bool shipFiredMissile, bool missileHitAsteroid, bool rocketEngineOn, bool missileHitShip);
};

#endif // SOUNDMANAGER_H
