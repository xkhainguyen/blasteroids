#include "menu.h"
#include "fssimplewindow.h"
#include <iostream>




int main(void)
{
    GameMenu menu;
    menu.SetButtons();
    FsOpenWindow(50,50,800,600,1);
    for(;;)
    {
        int menu_sel=menu.RunOneStep();
        if(GameMenu::BMENU_Start==menu_sel)
        {

            if (true==menu.isMultiplayer)
            {
                std::cout<<"the game has started, difficulty is:"<<menu.difficulty<< " there are two players";
            }
            else
            {
               std::cout<<"the game has started, difficulty is:"<<menu.difficulty<< " there is one player"; 
            }
            break;
        }
        else if (GameMenu::BMENU_QUIT==menu_sel)
        {
            std::cout<<"the user has exited the game";
            break;
        }
    }
    return 0;
}