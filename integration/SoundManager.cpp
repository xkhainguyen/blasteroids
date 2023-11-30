#include "SoundManager.h"
#include <iostream>

void SoundManager::Initialize(void)
{
    if(YSOK!=blaster.LoadWav("blaster.wav"))
    {
        std::cout << "Cannot load blaster.wav" << std::endl;
    }
    if(YSOK!=explosion.LoadWav("explosion2.wav"))
    {
        std::cout << "Cannot load explosion.wav" << std::endl;
    }
    if(YSOK!=rocketThrust.LoadWav("rocketThrust2.wav"))
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

void SoundManager::PlayThrust(void)
{
    player.PlayOneShot(rocketThrust);
}

void SoundManager::PlayTink(void)
{
    player.PlayOneShot(tink);
}

void SoundManager::PlayExplosion(void)
{
    player.PlayOneShot(explosion);
}

void SoundManager::PlayShoot(void)
{
    player.PlayOneShot(blaster);
}

