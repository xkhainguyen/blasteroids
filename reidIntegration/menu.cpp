#include "menu.h"
#include "fssimplewindow.h"
#include "ysglfontdata.h"
#include "background.h"

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

void Button::setMsg(std::string new_msg)
{
    msg=new_msg;
}

void Button::SetColor(int _r, int _g, int _b)
{
    r=_r;
    b=_b;
    g=_g;
}

bool Dropdown::check_mouse_posn(int mx,int my,int box_x, int box_y, int box_w, int box_h)
{
    return (mx>box_x && my>box_y && mx<box_x+box_w && my<box_y+box_h);
}

void Dropdown::setMsgs(std::vector<std::string> new_msgs)
{
    messages=new_msgs;
}

void Dropdown::expand(int lb, int mb,int rb,int mx,int my,int evt)
{
    int nm=messages.size();
    glColor3f(255,255,255);
    glBegin(GL_LINE_LOOP);
    glVertex2i(b1.x,b1.y+b1.h);
    glVertex2i(b1.x-drop_wid,b1.y+b1.h);
    glVertex2i(b1.x-drop_wid,b1.y+b1.h+20*nm);
    glVertex2i(b1.x,b1.y+b1.h+20*nm);
    glEnd(); 
    for (int i=0; i<nm;++i)
    {
        glRasterPos2d(b1.x-drop_wid+3,b1.y+b1.h+(i*20)+12);
        int v1x=b1.x-drop_wid+3;
        int v1y=b1.y+b1.h+(i*20);
        if(check_mouse_posn(mx,my,v1x,v1y,drop_wid-3,20))
        {
            glColor3f(0,255,255);
            glBegin(GL_QUADS);
            glVertex2i(v1x,v1y);
            glVertex2i(v1x+drop_wid-3,v1y);
            glVertex2i(v1x+drop_wid-3,v1y+20);
            glVertex2i(v1x,v1y+20);
            glEnd();
            glColor3f(255,255,255);
            if(FSMOUSEEVENT_LBUTTONDOWN==evt) 
            {
                closed_message=messages[i];
                return_val=i+1;
                drop_state="closed";
                b1.setMsg("v");
            }
        }
        YsGlDrawFontBitmap12x16(messages[i].c_str());
    }  
}

void::Dropdown::Draw(int lb, int mb,int rb,int mx,int my,int evt)
{
    b1.Draw();
    if ("open"==drop_state)
    {
        expand(lb,mb,rb,mx,my,evt);
    }
    glColor3ub(255,255,255);
    glRasterPos2d(b1.x-drop_wid+3,b1.y+20);
    YsGlDrawFontBitmap12x16(closed_message.c_str());
    glBegin(GL_LINE_LOOP);
    glVertex2i(b1.x-drop_wid,b1.y);
    glVertex2i(b1.x,b1.y);
    glVertex2i(b1.x,b1.y+b1.h);
    glVertex2i(b1.x-drop_wid,b1.y+b1.h);
    glEnd();
}

bool GameMenu::check_mouse_posn(int mx,int my,int box_x, int box_y, int box_w, int box_h)
{
    return (mx>box_x && my>box_y && mx<box_x+box_w && my<box_y+box_h);
}

void GameMenu::SetButtons()
{
    start.set(400,300,50,130,255,0,0,"Start Game");
    players_dd.b1.set(350,300,50,20,0,255,0,"v");
    diff_dd.b1.set(150,300,50,20,0,255,0,"v");
    std::vector<std::string> diffs={"easy","medium","hard"};
    std::vector<std::string> players={"one player","two player"};
    diff_dd.setMsgs(diffs);
    players_dd.setMsgs(players);
    players_dd.drop_wid=125;
}

int GameMenu::RunOneStep()
{
    int val=BMENU_None;
    int lb,mb,rb,mx,my;
    FsPollDevice();
    auto key=FsInkey();
    int evt=FsGetMouseEvent(lb,mb,rb,mx,my);
    start.SetColor(255,0,0);
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
    if(diff_dd.check_mouse_posn(mx,my,diff_dd.b1.x, diff_dd.b1.y, diff_dd.b1.w, diff_dd.b1.h) && FSMOUSEEVENT_LBUTTONDOWN==evt && "closed"==diff_dd.drop_state ||
        diff_dd.check_mouse_posn(mx,my,diff_dd.b1.x, diff_dd.b1.y, diff_dd.b1.w, diff_dd.b1.h)&& FSMOUSEEVENT_RBUTTONDOWN==evt && "closed"==diff_dd.drop_state)
        {
            diff_dd.drop_state="open";
            diff_dd.b1.setMsg("^");
        }
    else if(diff_dd.check_mouse_posn(mx,my,diff_dd.b1.x, diff_dd.b1.y, diff_dd.b1.w, diff_dd.b1.h) && FSMOUSEEVENT_LBUTTONDOWN==evt && "open"==diff_dd.drop_state ||
            diff_dd.check_mouse_posn(mx,my,diff_dd.b1.x, diff_dd.b1.y, diff_dd.b1.w, diff_dd.b1.h) && FSMOUSEEVENT_RBUTTONDOWN==evt && "open"==diff_dd.drop_state)
        {
            diff_dd.drop_state="closed";
            diff_dd.b1.setMsg("V");             
        }

    if(players_dd.check_mouse_posn(mx,my,players_dd.b1.x, players_dd.b1.y, players_dd.b1.w, players_dd.b1.h) && FSMOUSEEVENT_LBUTTONDOWN==evt && "closed"==players_dd.drop_state ||
        players_dd.check_mouse_posn(mx,my,players_dd.b1.x, players_dd.b1.y, players_dd.b1.w, players_dd.b1.h)&& FSMOUSEEVENT_RBUTTONDOWN==evt && "closed"==players_dd.drop_state)
        {
            players_dd.drop_state="open";
            players_dd.b1.setMsg("^");
        }
    else if(players_dd.check_mouse_posn(mx,my,players_dd.b1.x, players_dd.b1.y, players_dd.b1.w, players_dd.b1.h) && FSMOUSEEVENT_LBUTTONDOWN==evt && "open"==players_dd.drop_state ||
            players_dd.check_mouse_posn(mx,my,players_dd.b1.x, players_dd.b1.y, players_dd.b1.w, players_dd.b1.h)&& FSMOUSEEVENT_RBUTTONDOWN==evt && "open"==players_dd.drop_state)
        {
            players_dd.drop_state="closed";
            players_dd.b1.setMsg("V");             
        }
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    Background background;
    background.InitializeStars(100);
    background.DrawBackground();
    start.Draw();
    glColor3ub(255,255,255);
    glRasterPos2d(200,270);
    YsGlDrawFontBitmap10x14("Number of players");
    players_dd.Draw(lb,mb,rb,mx,my,evt);
    glRasterPos2d(50,270);
    YsGlDrawFontBitmap10x14("Difficulty");
    diff_dd.Draw(lb,mb,rb,mx,my,evt);
    glColor3f(0,255,0);
    glRasterPos2d(268,100);
    YsGlDrawFontBitmap24x40("BLASTEROIDS");
    FsSwapBuffers();
    difficulty=diff_dd.return_val;
    if (1==players_dd.return_val)
        isMultiplayer=false;
    else if(2==players_dd.return_val)
        isMultiplayer=true;
    return val;
}