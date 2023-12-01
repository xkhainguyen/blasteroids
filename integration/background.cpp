#include "background.h"
#include "fssimplewindow.h"
#include <vector>
#include <stdlib.h>
#include <cmath>

int window_width = 800;
int window_height = 600;
const double YS_PI = 3.1415927;



void Background::InitializeStars(int numStars) {
    starXPositions.clear();
    starYPositions.clear();

    for (int i = 0; i < numStars; ++i) {
        int x = rand() % 1024;
        int y = rand() % 1024;
        starXPositions.push_back(x);
        starYPositions.push_back(y);
    }
}

void Background::DrawBackground(void)
{
    // Black Background
    glColor3f(0.0f, 0.0f, 0.0f);  // Using glColor3f for consistency
    glBegin(GL_QUADS);
    glVertex2i(0,0);
    glVertex2i(1024,0);
    glVertex2i(1024,1024);
    glVertex2i(0,1024);
    glEnd();
    
    // Draw Stars
    glColor3f(1.0f,1.0f,1.0f);
    glPointSize(2.0f);

    for(size_t i = 0; i < starXPositions.size(); ++i)
    {
        glBegin(GL_POINTS);
        glVertex2i(starXPositions[i], starYPositions[i]);
        glEnd();
    }
}

