#include "pushbutton.h"
#include <iostream>

using namespace genv;
using namespace std;

PushButton::PushButton(Window *w, int x, int y, int sx, int sy,std::string s)
    : Widget(w,x,y,sx,sy)
{
    pushed = false;
    txt = s;
}
int f = 30;
void PushButton::draw(bool focused)
{
    int c = 150;
    if(focused)
        c=255;
    gout << font("LiberationSans-Regular.ttf",f);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    if(pushed)
        gout << move_to(_x+2, _y+2) << color(255,100,100) << box(_size_x-4, _size_y-4);
    else
        gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << color(c,c,c)<<move_to(_x+(_size_x/2)-4,_y+4+gout.cascent()+gout.cdescent()) << text(txt);
}
void PushButton::draw(int focused)
{
    /// 0-ures, 1-safe, 2-captured
    int r = 150;
    int g = 150;
    int b = 150;
    gout << font("LiberationSans-Regular.ttf",f);
    gout << move_to(_x, _y) << color(r,g,b) << box(_size_x, _size_y);
    if(focused == 0)
    {
        gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    }
    if(focused == 2)
    {
        r = 50;
        g = 50;
        b = 250;
        gout << move_to(_x+2, _y+2) << color(r,g,b) << box(_size_x-4, _size_y-4);
        gout << move_to(_x+4, _y+4) << color(0,0,0) << box(_size_x-8, _size_y-8);
    }
    if(focused == 1)
    {
        r = 50;
        g = 255;
        b = 50;
        gout << move_to(_x+2, _y+2) << color(r,g,b) << box(_size_x-4, _size_y-4);
        gout << move_to(_x+4, _y+4) << color(0,0,0) << box(_size_x-8, _size_y-8);
        return;
    }
    gout << color(r,g,b)<<move_to(_x+(_size_x/2)-4,_y+4+gout.cascent()+gout.cdescent()) << text(txt);
}

void PushButton::handle(event ev)
{
    if(ev.pos_x > _x && ev.pos_x < _x+_size_x && ev.pos_y > _y && ev.pos_y < _y+_size_y && btn_left > 0 && ev.button < 0 && !pushed)
    {
        pushed = !pushed;
    }
}

void PushButton::reset()
{
    pushed = false;
}

bool PushButton::get_current_value()
{
    return pushed;
}
std::string PushButton::get_current_text()
{
    return txt;
}
void PushButton::set_current_text(std::string s)
{
    txt = s;
}

