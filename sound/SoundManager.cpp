#include "SoundManager.h"

void SoundManager::Initialize(void)
{
    blaster.LoadWav("blaster.wav");
    explosion.LoadWav("explosion.wav");
    rocketThrust.LoadWav("rocket_thrust.wav");
    tink.LoadWav("tink.wav");
    mmlplayer.AddSegment(
        "@26T150L16V12 O5CDEFGAB>CBAGFEDC",  // Melody line, first phrase
        "@13T150L8S0M6000 O4GAB>C<D>E<F>G",  // Bass line, first phrase
        "@26T150L16V12 O6EFEDEDCDEFGFEDC",   // Counter melody, first phrase
        "O5CDEFGAB>CBAGFEDC",                // Melody line, second phrase
        "O3GAB>C<D>E<F>G",                   // Bass line, second phrase
        "O5EFEDEDCDEFGFEDC"                  // Counter melody, second phrase
    );
    mmlplayer.AddSegment(
        "@26T180L32V12 O6CGAGFEDC>GFEDCGF",  // Melody line, first phrase
        "@13T180L16S0M6000 O4D>F<A>D<F<A>D<F<A>",             // Bass line, first phrase
        "@26T180L32V12 O5FEDCDEFGABAGFEDC",                   // Counter melody, first phrase
        "O6CGAGFEDC>GFEDCGF",                // Melody line, second phrase
        "O4D>F<A>D<F<A>D<F<A",                                // Bass line, second phrase
        "O5FEDCDEFGABAGFEDC"                                  // Counter melody, second phrase
    );

    mmlplayer.AddSegment(
        "@26T140L8V12 O4E>G<C>E<G<C>E<G<C>",  // Melody line, first phrase
        "@13T140L8S0M6000 O3C<E>G<C<E>G<C<E>", // Bass line, first phrase
        "@26T140L8V12 O5G<B>D>G<B>D>G<B>D",   // Counter melody, first phrase
        "O4E>G<C>E<G<C>E<G<C",                // Melody line, second phrase
        "O3C<E>G<C<E>G<C<E",                  // Bass line, second phrase
        "O5G<B>D>G<B>D>G<B>D"                 // Counter melody, second phrase
    );
    mmlplayer.AddSegment(
        "@26T160L16V12 O5A>F<D>A<F<D>A<F<D",  // Melody line, first phrase
        "@13T160L16S0M6000 O4F<A<C<F<A<C<F<A", // Bass line, first phrase
        "@26T160L16V12 O6G>D<B>G<D<B>G<D<B",  // Counter melody, first phrase
        "O5A>F<D>A<F<D>A<F<D",                // Melody line, second phrase
        "O4F<A<C<F<A<C<F<A",                  // Bass line, second phrase
        "O6G>D<B>G<D<B>G<D<B"                 // Counter melody, second phrase
    );
    mmlplayer.AddSegment(
        "@26T150L4V12 O5C>G<C>G<C>G<C>G",   // Melody line, first phrase
        "@13T150L4S0M6000 O4E<A<E<A<E<A<E<A", // Bass line, first phrase
        "@26T150L4V12 O6G<B>G<B>G<B>G<B>",   // Counter melody, first phrase
        "O5C>G<C>G<C>G<C>G",                 // Melody line, second phrase
        "O4E<A<E<A<E<A<E<A",                 // Bass line, second phrase
        "O6G<B>G<B>G<B>G<B"                  // Counter melody, second phrase
    );
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

