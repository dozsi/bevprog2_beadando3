#include "pushbutton.h"
#include <iostream>

using namespace genv;

PushButton::PushButton(Window *w, int x, int y, int sx, int sy,std::string s)
    : Widget(w,x,y,sx,sy)
{
    pushed = false;
    txt = s;
}
int f = 20;
void PushButton::draw(bool focused)
{
    int c = 150;
    if(focused)
        c=255;
    gout << font("LiberationSans-Regular.ttf",f);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    if(pushed)
        gout << move_to(_x+2, _y+2) << color(100,100,100) << box(_size_x-4, _size_y-4);
    else
        gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << color(c,c,c)<<move_to(_x+4,_y+gout.cascent()+gout.cdescent()) << text(txt);
}

void PushButton::handle(event ev)
{
    if(ev.pos_x > _x && ev.pos_x < _x+_size_x && ev.pos_y > _y && ev.pos_y < _y+_size_y && btn_left > 0 && ev.type == ev_mouse)
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

