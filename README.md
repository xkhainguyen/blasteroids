# blasteroids

Game development project for CMU 24780

## How to develope

I do
gitignore on these

fssimplewindow.hpp;
fssimplewindow.cpp;
yssimplesound.hpp;
yssimplesound.cpp;
mmlplayer.hpp;
mmlplayer.cpp

so you have to copy your own system-dependent files into this directory.

Add your modules just like the ship.hpp and ship.cpp, then compile like this (on my Ubuntu).

```bash
g++ main.cpp ship.cpp [additional things]
```
