# blasteroids

Game development project for CMU 24780

## How to develop

I do
gitignore on these

fssimplewindow.hpp;
fssimplewindow.cpp;
yssimplesound.hpp;
yssimplesound.cpp;
mmlplayer.hpp;
mmlplayer.cpp

so you have to copy your own system-dependent files into your local directory.

Add your modules just like the ship.hpp and ship.cpp, then compile like this (on my Ubuntu).

```bash
g++ main.cpp ship.cpp [additional things]
```

## compiling menu test script

to complie the menu test script the following additional files must be included in the compile command along with `menu_test_script.cpp`
`menu.cpp fssimplewindow.cpp ysglfontdata.c`
