#ifndef BLASTEROIDS_MENU_H_IS_INCLUDED
#define BLASTEROIDS_MENU_H_IS_INCLUDED

#include <string>
class Button
{
    public:
        int x=0,y=0,h=0,w=0,r=0,g=0,b=0;
        std::string msg="";
        bool pushed=false;
        Button();
        void set(int _x,int _y,int _h,int _w,int _r,int _g, int _b,std::string _msg);
        void Draw();
        void SetColor(int _r, int _g, int _b);
};


class GameMenu
{
    protected:
    public:
        enum
        {
            BMENU_None,
            BMENU_Start,
            BMENU_QUIT

        };
        Button start;
        Button one_p;
        Button two_p;
        Button easy;
        Button medium;
        Button hard;
        char difficulty='X';
        bool isMultiplayer=false;
        void SetButtons();
        int RunOneStep (void);
        bool check_mouse_posn(int mx,int my,int box_x, int box_y, int box_w, int box_h);
};



#endif