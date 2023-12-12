# Blasteroids
Authors: Nikole Chetty, Reid Graves, Jeremy Kilbride, Vignesh Menon, Khai Nguyen, Pratik Satija, Anton Yanovich

## (1) Game Instructions

### (1.1) Game Menu
In the game menu there are two selections that the user must make: difficulty, and number of players. Do not start the game without making a selection for these two options. To make a selection, simply click the "v" button on each dropdown, then place your mouse cursor over the option you would like to select, and then click that option (can be left or right click). Once these two options are set, then place the mouse cursor over the start button, and then left or right click the start button to start the game.

### (1.2) Game Play

#### (1.2.1) Controls

Once the game has started the player(s) must destroy asteroids by shooting them while also ensuring that their ship does not collide with any asteroids. For single player mode controls are: 
* &larr; key: rotate the ship counter-clockwise 
* &rarr; key: rotate the ship clockwise
* &uarr; key: thrust
* space key: shoot

For two player mode the controls are:
* player one: 
    * same as above
* player two:
    * &#127280; : rotate the player two ship counter-clockwise
    * &#127283; : rotate the player two ship clockwise
    * &#127302; : thrust player two
    * &#127296; : shoot for player two

#### (1.2.2) Game over conditions

The game will end in two possible ways:
1. All asteroids are destroyed on all levels. When all asteroids for a single level are destroyed, the game will progress to the next level. This will continue until all levels are completed
2. All ships are destroyed. A ship will be destroyed if it collides with an asteroid

## (2) Compile instructions

### (2.1) Prerequisites
 Please ensure you have the proper versions of `fssimplewindow`, `yssimplesound`,  and `mmlplayer`, for your OS in the directory where you would like to compile the project. Also, please ensure the following sound files are in that directory:
 * `music.wav`
 * `intro.wav`
 * `blaster.wav`
 * `explosion2.wav`
 * `rocketThrust2.wav`
 * `tink.wav`

 Additionally please ensure all necessary source and header files are included in the directory in which you will compile the program. The necessary files are:
 * `menu.h`, `menu.cpp`
 * `background.h `, `background.cpp`
 * `asteroid.h`,  `asteroid.cpp`
 * `ship.h`, `ship.cpp`
 * `asteroid_manager.hpp`, `asteroid_manager.cpp`
 * `SoundManager.h`, `SoundManager.cpp`
 * `summary.hpp`, `summary.cpp`
 * `explosion.h`, `explosion.cpp`

### (2.2.1) Visual C++
use the following compile command for visual c++:

```
cl /EHsc integrate.cpp menu.cpp fssimplewindow.cpp ysglfontdata.c yssimplesound.cpp mmlplayer.cpp background.cpp asteroid.cpp asteroid_manager.cpp ship.cpp SoundManager.cpp summary.cpp explosion.cpp
```

### (2.2.2) Clang
use the following compile command for clang:

```
clang++ -std=c++11 -Wno-deprecated-declarations -o test.app/Contents/MacOS/exe integrate.cpp fssimplewindowcpp.cpp fssimplewindowobjc.o yssimplesound.cpp yssimplesound_macosx_objc.o SoundManager.cpp asteroid.cpp background.cpp summary.cpp ship.cpp asteroid_manager.cpp menu.cpp explosion.cpp ysglfontdata.c -framework Cocoa -framework OpenGL -framework AVfoundation
```


## (3) External Packages

No external packages were used for this project. All included packages are either part of STL or provided in class
