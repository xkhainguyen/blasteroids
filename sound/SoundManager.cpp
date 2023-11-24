#include "SoundManager.h"
#include <iostream>

void SoundManager::Initialize(void)
{
    if(YSOK!=blaster.LoadWav("blaster.wav"))
    {
        std::cout << "Cannot load blaster.wav" << std::endl;
    }
    if(YSOK!=explosion.LoadWav("explosion.wav"))
    {
        std::cout << "Cannot load explosion.wav" << std::endl;
    }
    if(YSOK!=rocketThrust.LoadWav("rocketThrust.wav"))
    {
        std::cout << "Cannot load rocketThrust.wav" << std::endl;
    }
    if(YSOK!=tink.LoadWav("tink.wav"))
    {
        std::cout << "Cannot load tink.wav" << std::endl;
    }
    if(YSOK!=music.LoadWav("music.wav"))
    {
        std::cout << "Cannot load music.wav" << std::endl;
    }
}

void SoundManager::PlayMusic(void)
{
    player.PlayBackground(music);
}

void SoundManager::PlaySound(bool shipFiredMissile, bool missileHitAsteroid, bool rocketEngineOn, bool missileHitShip)
{
    if (shipFiredMissile)
    {
        player.PlayOneShot(blaster);
    }
    else if (missileHitAsteroid)
    {
        player.PlayOneShot(explosion);
    }
    else if (rocketEngineOn)
    {
        player.PlayOneShot(rocketThrust);
    }
    else if (missileHitShip)
    {
        player.PlayOneShot(tink);
    }
}

