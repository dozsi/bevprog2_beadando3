#include "label.h"

using namespace genv;

Label::Label(Window *w, int x, int y, int sx, int sy,int s)
    : Widget(w,x,y,sx,sy)
{
    txt = s;
}
int k = 20;
void Label::draw(bool focused)
{
    int c = 150;
    if(focused)
        c=255;
    gout << font("LiberationSans-Regular.ttf",k);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(50,50,50) << box(_size_x-4, _size_y-4);
    gout << color(c,c,c)<<move_to(_x+4,_y+gout.cascent()+gout.cdescent()) << text(std::to_string(txt));
}
void Label::set_text(int s)
{
    txt = s;
}
void Label::handle(event ev)
{
}


