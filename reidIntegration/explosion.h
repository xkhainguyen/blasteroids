#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "fssimplewindow.h"

class Explosion
{
    public:
        enum
        {
            NUM_PARTICLES=64
        };
        class Particle
        {
            public:
                unsigned char r,g,b;
                int x,y,vx,vy;
        };
        int step=0;
        int state=0;
        std::vector<Particle> particles;
        void Explode(int x, int y);
        void Move(void);
        void Draw(void);
};

#endif // EXPLOSION_H
