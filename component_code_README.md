## Individual Compenent Code

Each folder within this repository represents the component code of a different team member. Below each folder's contents are briefly described along with listing the author of the files
* menu-Author: Jeremy Kilbride
  * Three files to build and test the functionality of the game menu:
    * menu.cpp-source code for the game menu class and button class. The menu has one function `RunOneStep()` which detects user interaction with various buttons and stores some variable values based un users selection at each iteration
    * menu.h-header file for menu and button class with class and member function prototypes
    * menu_test_script.cpp-a simple way to test the functionality of the menu
* ship-Author: Vignesh Menon
  * Responsible for creating and controlling the spaceships. 
    * ship.h-Header for Ship Component of the game. The code in this header file defines two classes, ‘Missile’ and ‘Ship’.  The ‘Missile’ class represents a projectile with properties such as coordinates, velocity, and status, and it includes methods to activate, shoot, disappear, and draw the missile. The ‘Ship’ class represents a player's ship in a game, with attributes like coordinates, maximum window coordinates, player number, its own  missile array, and other properties. The class includes methods to draw the ship, shoot missiles, trigger missile activation, check for collisions with missiles and other ships, retrieve ship coordinates, and move the ship in different directions. The code uses the fssimplewindow library for graphics.
    * ship.cpp-The code in "ship.cpp" defines the member functions for the previously declared classes in "ship.h." The ‘Missile’ class contains methods to activate, shoot, disappear, and draw a missile. The ‘Shoot’ method updates the missile's position based on its velocity and causes it to disappear when reaching the top of the screen. The ‘Draw’ method renders the missile on the screen using OpenGL primitives. The ‘Ship’ class defines methods to draw the player's ship, shoot missiles, trigger missile activation, and handle ship movements in different directions. The collision detection functions determine whether a missile collides with another player's ship, updating relevant properties and causing missiles to disappear upon collision. Additionally, there are methods for retrieving the ship's coordinates and handling movement boundaries. The code uses OpenGL graphics functions and includes the necessary header file for graphics operations.
    * shipTest-The code in "shipTest.cpp" serves as a test program for the functionality of the ‘Ship’ and ‘Missile’ classes defined in the "ship.h" and "ship.cpp" files. The program initializes two player ships with specific starting positions and sets up a window using the fssimpleWindow library. The main loop of the program handles user input for ship movements and missile firing, updating the positions of the ships accordingly. The program checks for collisions between missiles and the opposing player's ship, keeping track of the number of friendly fire incidents. The graphics are rendered using OpenGL functions, and the program continuously updates and displays the game state. The loop exits when the user presses the ESC key. After the loop, the program outputs the number of missiles each player has shot and the total number of friendly fire incidents. This test program provides a simulation of a simple two-player game involving ship movements, missile firing, and collision detection.
   
* sound-Author: Reid Graves
  * SoundManager.h-Header for sound manager: Defines sound manager class, class members, initialize function and PlaySound Function. The player members are a player for .wav files and the mml player, respectively. The sound data members are for storing the wav files for game sounds
  * SoundManager.cpp-Source file for sound manager. The initialize function passes the wave files to the sound data members, and adds the mml segments to the mml player.The PlaySound function takes in outside boolean members. It is assumed that each instance of a sound will correspond to a state within the game. For example, if a missile hits an asteroid, then the state of a missile (and asteroid) will change. So at the beginning of a while loop, if all state variables are passed to the PlaySound function, as soon as a state variable changes to true (missile hit asteroid in this example) then the respective sound is played.  
  * SoundManagerTestMain.cpp-This is the test script for the SoundManager class, header, and source files. Given the assumption of state use outlined in the SoundManager.cpp section above, keystates are used to simulate a state variable changing. On my machine the SoundManager behaved as expected, although there is some refinement that I will do to make the wave files played in succession to sound smoother. For instance, the rocketThrust sound has a clipping sound due to the wave file being cut off at different points in the wave, and I would like it to sound continuous. Additionally, I am going to implement a stop player condition for the rocket ship that prevents the rocket thrust sound from playing after the thrust button is released.
 
* asteroid-Author: Anton Yanonvich
  * Classes: asteroid.hpp/.cpp asteroid_manager.hpp/.cpp asteroid_test.cpp
    * Created a model for physical interaction between asteroids
    * Established baseline game logic for asteroids and their destruction
    * Created a raw demonstration of asteroid object initialization and behavior in the game
   
* game-Author: Nikole Chetty
  * game.cpp-Has mock implementations of the six subclasses: Menu, Ship, Asteroid, Sound, Background, and Summary
Implements the master game class which initializes the classes, then renders and updates the game, until and end game condition is met
The game is tested by the main loop

* summary-Author: Khai Nguyen
  * Class PlayerStats (to be included in class Ship or Player) define all the game statistics (bullets shot, asteroid hit, time, score) for each player for each level. It has several methods to be called by the game master when a corresponding event happens. It can also compute the total score after each level.
  * Class Player is a dummy class for testing purposes. This includes the PlayerStats.
  * Class GameSummary defines what we want to show at the end of each level and after credit and methods to print them out on the screen. Game master will call the methods at the right time. Right now they are just printing to the terminal.
  * I have a `test` script to check if everything is working as expected.
 
* background-Author: Pratik Satija
  * The background functionality has been modularized into a Sphere Class, along with two supporting functions: DrawSphere and DrawBackground. These components have been defined in my background header file. The actual implementation of the Sphere Class and functions has been specified in the corresponding .cpp file. To streamline the testing process effectively, I opted to merge my code with the existing GameMenu test code. This approach not only facilitated a comprehensive understanding of my teammate's coding style but also set the groundwork for smoother integration of different code segments in the future. This collaborative approach enhances our team's overall efficiency and cohesion. 
 
