#include "menu.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"

void Button::Draw()
{
	glColor3f(r,g,b);
	glBegin(GL_QUADS);
	glVertex2i(x,y);
	glVertex2i(x+w,y);
	glVertex2i(x+w,y+h);
	glVertex2i(x,y+h);
	glEnd();
    glColor3f(0,0,0);
    glRasterPos2i(x+5,y+30);
    YsGlDrawFontBitmap12x16(msg.c_str());
}
Button::Button()
{
}

void Button::set(int _x,int _y,int _h,int _w,int _r,int _g, int _b,std::string _msg)
{
    x=_x;
    y=_y;
    h=_h;
    w=_w;
    r=_r;
    g=_g;
    b=_b;
    msg=_msg;
}

void Button::SetColor(int _r, int _g, int _b)
{
    r=_r;
    b=_b;
    g=_g;
}

bool GameMenu::check_mouse_posn(int mx,int my,int box_x, int box_y, int box_w, int box_h)
{
    return (mx>box_x && my>box_y && mx<box_x+box_w && my<box_y+box_h);
}

void GameMenu::SetButtons()
{
    start.set(335,325,50,130,255,0,0,"Start Game");
    one_p.set(70,70,50,130,255,0,0,"One Player");
    two_p.set(600,70,50,130,255,0,0,"Two Player");
    easy.set(70,200,50,60,255,0,0,"Easy");
    medium.set(350,200,50,100,255,0,0,"Medium");
    hard.set(670,200,50,60,255,0,0,"Hard");
}

int GameMenu::RunOneStep()
{
    int val=BMENU_None;
    int lb,mb,rb,mx,my;
    FsPollDevice();
    auto key=FsInkey();
    int evt=FsGetMouseEvent(lb,mb,rb,mx,my);
    start.SetColor(255,0,0);
    if(false==easy.pushed)
    {
        easy.SetColor(255,0,0);
    }
    if(false==medium.pushed)
    {
        medium.SetColor(255,0,0);
    }
    if(false==hard.pushed)
    {
        hard.SetColor(255,0,0);
    }
    if(false==one_p.pushed)
    {
        one_p.SetColor(255,0,0);
    }
    if(false==two_p.pushed)
    {
        two_p.SetColor(255,0,0);
    }
    if (FSKEY_ESC==key)
    {
        val=BMENU_QUIT;
    }

    if (check_mouse_posn(mx,my,start.x,start.y,start.w,start.h))
    {
        start.SetColor(255,255,0);
        if(FSMOUSEEVENT_LBUTTONDOWN==evt || FSMOUSEEVENT_RBUTTONDOWN==evt)
        {
            start.SetColor(0,255,0);
            val=BMENU_Start;
        }
    }
    if (check_mouse_posn(mx,my,easy.x,easy.y,easy.w,easy.h))
    {
        easy.SetColor(255,255,0);
        medium.SetColor(255,0,0);
        hard.SetColor(255,0,0);
        if(FSMOUSEEVENT_LBUTTONDOWN==evt || FSMOUSEEVENT_RBUTTONDOWN==evt)
        {
            easy.pushed=true;
            hard.pushed=false;
            medium.pushed=false;
            difficulty='e';
        }
    }
    if (check_mouse_posn(mx,my,medium.x,medium.y,medium.w,medium.h))
    {
        easy.SetColor(255,0,0);
        medium.SetColor(255,255,0);
        hard.SetColor(255,0,0);
        if(FSMOUSEEVENT_LBUTTONDOWN==evt || FSMOUSEEVENT_RBUTTONDOWN==evt)
        {
            medium.pushed=true;
            easy.pushed=false;
            hard.pushed=false;
            difficulty='m';
            
        }
    }
    if (check_mouse_posn(mx,my,hard.x,hard.y,hard.w,hard.h))
    {
        hard.SetColor(255,255,0);
        easy.SetColor(255,0,0);
        medium.SetColor(255,0,0);
        if(FSMOUSEEVENT_LBUTTONDOWN==evt || FSMOUSEEVENT_RBUTTONDOWN==evt)
        {
            hard.pushed=true;
            easy.pushed=false;
            medium.pushed=false;
            difficulty='h';
        }
    }
    if (check_mouse_posn(mx,my,one_p.x,one_p.y,one_p.w,one_p.h))
    {
        one_p.SetColor(255,255,0);
        two_p.SetColor(255,0,0);
        if(FSMOUSEEVENT_LBUTTONDOWN==evt || FSMOUSEEVENT_RBUTTONDOWN==evt)
        {
            one_p.pushed=true;
            two_p.pushed=false;
            isMultiplayer=false;
        }
    }
    if (check_mouse_posn(mx,my,two_p.x,two_p.y,two_p.w,two_p.h))
    {
        one_p.SetColor(255,0,0);
        two_p.SetColor(255,255,0);
        if(FSMOUSEEVENT_LBUTTONDOWN==evt || FSMOUSEEVENT_RBUTTONDOWN==evt)
        {
            two_p.pushed=true;
            one_p.pushed=false;
            isMultiplayer=true;
        } 
    }
    if(true==easy.pushed)
    {
        easy.SetColor(0,255,0);
    }
    if(true==medium.pushed)
    {
        medium.SetColor(0,255,0);
    }
    if(true==hard.pushed)
    {
        hard.SetColor(0,255,0);
    }
    if(true==one_p.pushed)
    {
        one_p.SetColor(0,255,0);
    }
    if(true==two_p.pushed)
    {
        two_p.SetColor(0,255,0);
    }
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    start.Draw();
    one_p.Draw();
    two_p.Draw();
    easy.Draw();
    medium.Draw();
    hard.Draw();
    FsSwapBuffers();
    return val;
}