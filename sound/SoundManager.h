#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "yssimplesound.h"

class SoundManager
{
public:
    YsSoundPlayer player;
    YsSoundPlayer player2;
    YsSoundPlayer::SoundData blaster;
    YsSoundPlayer::SoundData explosion;
    YsSoundPlayer::SoundData rocketThrust;
    YsSoundPlayer::SoundData tink;
    YsSoundPlayer::SoundData music;

    void Initialize(void);
    void PlayMusic(void);
    void PlaySound(bool shipFiredMissile, bool missileHitAsteroid, bool rocketEngineOn, bool missileHitShip);
};

#endif // SOUNDMANAGER_H

