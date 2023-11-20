#include "menu.h"
#include "fssimplewindow.h"
#include <iostream>
#include "background.h"


int main(void)
{
    GameMenu menu;
    menu.SetButtons();
    FsOpenWindow(50,50,800,600,1);
    for(;;)
    {
        
        int menu_sel=menu.RunOneStep();
        // if(GameMenu::BMENU_Start==menu_sel)
        // {
        //     std::cout<<"the game has started, difficulty is:"<<menu.difficulty<< " there are "<<menu.n_player<<" players";
        //     break;
        // }
        // else if (GameMenu::BMENU_QUIT==menu_sel)
        // {
        //     std::cout<<"the user has exited the game";
        //     break;
        // }
    }
    return 0;
}