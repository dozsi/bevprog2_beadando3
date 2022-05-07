#include "spinbox.h"

using namespace genv;

SpinBox::SpinBox(Window *w, int x, int y, int sx, int sy, int min, int max)
    : Widget(w,x,y,sx,sy)
{
    num = min;
    mini = min;
    maxi = max;
}
int d = 20;
void SpinBox::draw(bool focused)
{
    int c = 150;
    if(focused)
        c=255;
    gout << font("LiberationSans-Regular.ttf",d);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+_size_x-d,_y) << color(c,c,c) << line_to(_x+_size_x-d,_y+_size_y-2);
    gout << move_to(_x+_size_x-d,_y+(_size_y/2)) << line_to(_x+_size_x-2,_y+(_size_y/2));
    gout << move_to(_x+_size_x-d+2,_y+(_size_y/2)-5) << line_to(_x+_size_x-1-(d/2),_y+5) << line_to(_x+_size_x-4,_y+(_size_y/2)-5);
    gout << move_to(_x+_size_x-d+2,_y+(_size_y/2)+5) << line_to(_x+_size_x-1-(d/2),_y+_size_y-5) << line_to(_x+_size_x-4,_y+(_size_y/2)+5);
    gout << move_to(_x+_size_x/2-gout.twidth(std::to_string(num)),_y+gout.cascent()+gout.cdescent()+_size_y/2-12) << text(std::to_string(num));
}

void SpinBox::add(int n)
{
    num += n;
    if(num<mini)
        num=mini;
    else if(num>maxi)
        num=maxi;
}

void SpinBox::handle(event ev)
{
    if(ev.pos_x > _x+_size_x-d && ev.pos_x < _x+_size_x && ev.pos_y > _y && ev.pos_y < _y+_size_y && ev.button < 0 && ev.type == ev_mouse)
    {
        if(ev.pos_y > _y+(_size_y/2))
            add(-1);
        else
            add(1);
    }
    else if(ev.keycode == -82)
         add(1);
    else if(ev.keycode == -81)
         add(-1);
    else if(ev.keycode == -75)
         add(10);
    else if(ev.keycode == -78)
         add(-10);
}

int SpinBox::get_current_value()
{
    // meglepcsi
    return num + 1;
}

