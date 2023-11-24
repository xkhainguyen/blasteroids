#include <math.h>
#include <vector>
#include <stdlib.h>

#include "fssimplewindow.h"
#include "SoundManager.h"

#define Pi 3.14159265358979323846

class Background {
public:
    std::vector<int> starXPositions;
    std::vector<int> starYPositions;

    void InitializeStars(int numStars);
    void DrawBackground(void);
};

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


class SpaceShip
{
public:
    int x, y, size, w, h, Nh, Fh, Fw;
    bool isFlying;
    bool isThrust;
    double degAng, deltaY, deltaX, velX, velY;

    // Constructor
    SpaceShip() : x(0), y(0), size(20), w(10), h(20), Nh(10), Fh(4), Fw(5), deltaY(0), deltaX(0), isFlying(false), degAng(0), velX(0), velY(0) {}

    // Function to initialize variables
    void Initialize(int startX, int startY, int startSize, int startDeltaY, int startDeltaX, bool startIsFlying, double startDegAng);

    // Functions for drawing and flying
    void DrawSpaceShip(void);
    void FlySpaceShip(void);
    void UpdateAngle();
};

// SpaceShip functions
void SpaceShip::Initialize(int startX, int startY, int startSize, int startDeltaY, int startDeltaX, bool startIsFlying, double startDegAng)
{
    x = startX;
    y = startY;
    size = startSize;
    w = (int)size/2;
    h = size;
    Nh = (int)size/2;
    Fh = (int)size/3;
    Fw = (int)size/2;
    deltaY = startDeltaY;
    deltaX = startDeltaX;
    isFlying = startIsFlying;
    degAng = startDegAng;
}

/*void SpaceShip::DrawSpaceShip()
{
    double ang = degAng * Pi / 180;
    double s = sin(ang);
    double c = cos(ang);

        // Set spaceship body color
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray
    // Draw the spaceship body (main body)
    glBegin(GL_QUADS); // Use GL_QUADS to make it oblong
    // Upper left corner
    glVertex2d(x, y);
    // Upper right corner
    glVertex2d((x + size*c), (y-size*s));
    // Lower right corner
    glVertex2d((x + size*c + 2*size*s), (y + 2*size*c - size*s));
    // Lower left corner
    glVertex2d((x + 2*size*s), (y + 2*size*c));
    glEnd();
    // Set fins' color
    glColor3f(0.5f, 0.5f, 0.5f); // Dark gray
    // Draw the triangular fins on the sides
    glBegin(GL_TRIANGLES);
    // Left fin (triangle)
    glVertex2d(x + 2*size*s, y + 2*size*c);//bottom vertex
    glVertex2d(x - .5*size*c + 2*size*s, y + 2*size*c + 0.5*size*s);//middle vertex
    glVertex2d(x + size*(2-0.5)*s, y + 1.5*size*c);//top vertex
    // Right fin (triangle)
    glVertex2d(x + size*c + 2*size*s, y + 2*size*c - size*s);// bottom vertex
    glVertex2d(x + 1.5*size*c + 2*size*s, y + 2*size*c - 1.5*size*s);// middle vertex
    glVertex2d(x + size*c + 1.5*size*s, y + 1.5*size*c - size*s);// top vertex
    glEnd();
    // Set nose color
    glColor3f(1.0f, 1.0f, 1.0f); // white
    // Draw the nose cone (triangle)
    glBegin(GL_TRIANGLES);
    // Top vertex of the nose cone
    glVertex2d(x, y);
    // Left vertex of the nose cone
    glVertex2d(x + 0.5*size*c-.75*size*s, y - 0.75*size*c - 0.5*size*s);
    // Right vertex of the nose cone
    glVertex2d(x + size*c, y-size*s);
    glEnd();
}
*/

void SpaceShip::DrawSpaceShip()
{
    double ang = degAng * Pi / 180;
    double s = sin(ang);
    double c = cos(ang);

    // Center of the spaceship
    int centerX = x;
    int centerY = y;

    // Set spaceship body color
    glColor3f(0.8f, 0.8f, 0.8f); // Light gray
    // Draw the spaceship body (main body)
    glBegin(GL_QUADS);
    // Upper left corner
    glVertex2d(centerX - w*c*.5 + h*s*.5, centerY - h*c*.5 - w*s*.5);
    // Upper right corner
    glVertex2d(centerX + w*c*.5 + h*s*.5, centerY - h*c*.5 + w*s*.5);
    // Lower right corner
    glVertex2d(centerX + w*c*.5 - h*s*.5, centerY + h*c*.5 + w*s*.5);
    // Lower left corner
    glVertex2d(centerX - w*c*.5 - h*s*.5, centerY + h*c*.5 - w*s*.5);
    glEnd();

    // Set fins' color
    glColor3f(0.5f, 0.5f, 0.5f); // Dark gray
    // Draw the triangular fins on the sides
    glBegin(GL_TRIANGLES);
    // Left fin (triangle)
    glVertex2d(centerX - w*c*.5 - h*s*.5, centerY + h*c*.5 - w*s*.5); // Bottom vertex
    glVertex2d(centerX - (w*.5 + Fw)*c - h*s*.5, centerY + h*c*.5 -(w*.5 + Fw)*s); // Middle vertex
    glVertex2d(centerX - w*c*.5 -(h*.5 - Fh)*s, centerY + (h*.5 - Fh)*c - w*s*.5); // Top vertex
    // Right fin (triangle)
    glVertex2d(centerX + w*c*.5 - h*s*.5, centerY + h*c*.5 + w*s*.5); // Bottom vertex
    glVertex2d(centerX + (w*.5 + Fw)*c - h*s*.5, centerY + h*c*.5 + (w*.5 + Fw)*s); // Middle vertex
    glVertex2d(centerX + w*c*.5 - (h*.5 - Fh)*s, centerY + (h*.5 - Fh)*c + w*s*.5); // Top vertex
    glEnd();

    // Set nose color
    glColor3f(1.0f, 1.0f, 1.0f); // White
    // Draw the nose cone (triangle)
    glBegin(GL_TRIANGLES);
    // Top vertex of the nose cone
    glVertex2d(centerX + (h*.5 + Nh)*s, centerY - (h*.5 + Nh)*c);
    // Left vertex of the nose cone
    glVertex2d(centerX - w*c*.5 + h*s*.5, centerY - h*c*.5 - w*s*.5);
    // Right vertex of the nose cone
    glVertex2d(centerX + w*c*.5 + h*s*.5, centerY - h*c*.5 + w*s*.5);
    glEnd();
}


void SpaceShip::FlySpaceShip(void)
{
    double ang = degAng * Pi / 180;
    double s = sin(ang);
    double c = cos(ang);

    x+=velX;
    y+=velY;

    if (x<0)
    {
        x += 1024;
    }
    else if (x >= 1024)
    {
        x -= 1024;
    }

    if (y < 0)
    {
        y += 1024;
    }
    else if (y>=1024)
    {
        y-=1024;
    }

    if(isFlying)
    {
        velY -= deltaY * c;
        velX += deltaX * s;

        int numFlames = 200;  // number of flames to generate
        glBegin(GL_LINES);

        for(int i = 0; i < numFlames; ++i)
        {
            // Randomize the color to shades of red and orange
            unsigned char red = 200 + rand() % 56;  // 200 to 255
            unsigned char green = 50 + rand() % 56; // 50 to 105
            unsigned char blue = 0;                 // 0
            glColor3ub(red, green, blue);

            // Calculate the start point for flame (back of the spaceship)
            int randstart = rand() % w;
            int xf1 = x - w*c/2 - (h*.5 + Fh)*s + randstart*c; // Adjusted for center reference
            int yf1 = y - w*s/2 + (h*.5 + Fh)*c + randstart*s; // Adjusted for center reference

            // Randomize the length and direction of the flame lines
            int length = rand() % 20 + 10;  // flame length between 10 and 30 (adjust as needed)
            double flameAngle = ang + (rand() % 20 - 10) * Pi / 180; // Random angle deviation

            double flameS = sin(flameAngle);
            double flameC = cos(flameAngle);

            // Calculate the end point of the line
            int xf2 = xf1 - flameS*length;
            int yf2 = yf1 + length * flameC;

            // Draw the line
            glVertex2i(xf1, yf1);
            glVertex2i(xf2, yf2);
        }

        glEnd();
    }
}

int main(void)
{
    FsOpenWindow(0, 0, 1024, 1024, 1);
    FsChangeToProgramDir();
    
    Background background;
    background.InitializeStars(100);
    SpaceShip spaceship;
    spaceship.Initialize(300, 400, 20, 1, 1, false, 0);

    SoundManager soundManager;
    soundManager.Initialize();

	soundManager.player.Start();
	soundManager.PlayMusic();
    
    bool shipFiredMissile = false;
    bool missileHitAsteroid = false;
    bool rocketEngineOn = false;
    bool missileHitShip = false;
    
    for (;;)
    {
        FsPollDevice();
        auto key = FsInkey();

        if (FSKEY_ESC == key)
        {
            break;
        }
        else if (FSKEY_LEFT == key)
        {
            spaceship.degAng -= 10;
        }
        else if (FSKEY_RIGHT == key)
        {
            spaceship.degAng += 10;
        }
        else if (FSKEY_UP == key)
        {
            spaceship.isFlying = true;
            spaceship.isThrust = true;
            rocketEngineOn = true;
        }
        else if (FSKEY_DOWN == key)
        {
            spaceship.isFlying = false;
        }
        else if (spaceship.isThrust == true && FSKEY_UP != key)
        {
            spaceship.isFlying = false;
            rocketEngineOn = false;
        }
        soundManager.PlaySound(shipFiredMissile, missileHitAsteroid, rocketEngineOn, missileHitShip);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        background.DrawBackground();
        spaceship.DrawSpaceShip();
        spaceship.FlySpaceShip();
        FsSwapBuffers();
        FsSleep(20);
    }
    
    return 0;
}
