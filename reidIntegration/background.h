#ifndef BLASTEROIDS_SPHERE_H_IS_INCLUDED
#define BLASTEROIDS_SPHERE_H_IS_INCLUDED
#include <stdlib.h>
#include <vector>


class Background {
public:
    std::vector<int> starXPositions;
    std::vector<int> starYPositions;

    void InitializeStars(int numStars);
    void DrawBackground(void);
};

#endif