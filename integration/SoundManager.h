#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "yssimplesound.h"

class SoundManager
{
public:
    YsSoundPlayer player;
    YsSoundPlayer::SoundData blaster;
    YsSoundPlayer::SoundData explosion;
    YsSoundPlayer::SoundData rocketThrust;
    YsSoundPlayer::SoundData tink;
    YsSoundPlayer::SoundData music;

    void Initialize(void);
    void PlayMusic(void);
    void PlayThrust(void);
    void PlayTink(void);
    void PlayExplosion(void);
    void PlayShoot(void);
};

#endif // SOUNDMANAGER_H

