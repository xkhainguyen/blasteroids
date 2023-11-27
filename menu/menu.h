#ifndef BLASTEROIDS_MENU_H_IS_INCLUDED
#define BLASTEROIDS_MENU_H_IS_INCLUDED
#include <vector>
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
        void setMsg(std::string new_msg);
};

class Dropdown
{
    public:
        Button b1;
        int drop_wid=80;
        std::vector<std::string> messages;
        int return_val=0;
        std::string closed_message;
        std::string drop_state="closed";
        void Draw(int lb, int mb,int rb,int mx,int my,int evt);
        void expand(int lb, int mb,int rb,int mx,int my,int evt);
        bool check_mouse_posn(int mx,int my,int box_x, int box_y,int box_w, int box_h);
        void setMsgs(std::vector<std::string> new_msgs);  
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
        Dropdown players_dd;
        Dropdown diff_dd;
        int difficulty=0;//1-> easy, 2-> medium, 3 -> hard
        bool isMultiplayer=false;
        void SetButtons();
        int RunOneStep (void);
        bool check_mouse_posn(int mx,int my,int box_x, int box_y, int box_w, int box_h);
};



#endif