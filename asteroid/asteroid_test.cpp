#include "fssimplewindow.h"
#include "asteroid_manager.hpp"
#include <cstdlib>

int main() {
    FsOpenWindow(0, 0, 800, 600, 1);

    int DIFFICULTY_LEVEL = 3;
    int ASTEROID_COUNT = 10;

    AsteroidManager manager = AsteroidManager();

    manager.initialize(DIFFICULTY_LEVEL, 800, 600, ASTEROID_COUNT);

    while (true) {
        FsPollDevice();
        if (FsGetKeyState(FSKEY_ESC)) {
            break;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (FsInkey() == FSKEY_B) {
            if (!manager.getCurrentAsteroids().empty()) {
                size_t index = rand() % manager.getCurrentAsteroids().size();
                manager.destroyAsteroid(index);
            }
        }

        std::cout << "Asteroids: " << manager.getCurrentAsteroids().size() << std::endl;

        glColor3ub(0, 0, 255);
        glBegin(GL_QUADS);
        glVertex2i(0, 0);
        glVertex2i(800, 0);
        glVertex2i(800, 600);
        glVertex2i(0, 600);
        glEnd();

        manager.drawAsteroids();
        manager.updateAsteroids();

        FsSwapBuffers();
        FsSleep(25);
    }

    return 0;
}