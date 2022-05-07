#include "spinbox.h"

using namespace genv;

SpinBox::SpinBox(Window *w, int x, int y, int sx, int sy, int min, int max)
    : Widget(w,x,y,sx,sy)
{
    num = min;
}
void SpinBox::draw()
{
    int c = 150;
    int d = 20;
    gout  << font("LiberationSans-Regular.ttf",20);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+_size_x-d,_y) << color(c,c,c) << line_to(_x+_size_x-d,_y+_size_y-2);
    gout << move_to(_x+_size_x-d,_y+(_size_y/2)) << line_to(_x+_size_x-2,_y+(_size_y/2));
    gout << move_to(_x+_size_x-d+2,_y+(_size_y/2)-5) << line_to(_x+_size_x-1-(d/2),_y+5) << line_to(_x+_size_x-4,_y+(_size_y/2)-5);
    gout << move_to(_x+_size_x-d+2,_y+(_size_y/2)+5) << line_to(_x+_size_x-1-(d/2),_y+_size_y-5) << line_to(_x+_size_x-4,_y+(_size_y/2)+5);
    gout << move_to(_x,_y) << text(std::to_string(num));
}
void SpinBox::draw_focused()
{
    int c = 255;
    int d = 20;
    gout  << font("LiberationSans-Regular.ttf",20);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+_size_x-d,_y) << color(c,c,c) << line_to(_x+_size_x-d,_y+_size_y-2);
    gout << move_to(_x+_size_x-d,_y+(_size_y/2)) << color(c,c,c) << line_to(_x+_size_x-2,_y+(_size_y/2));
    gout << move_to(_x+_size_x-d+2,_y+(_size_y/2)-5) << line_to(_x+_size_x-1-(d/2),_y+5) << line_to(_x+_size_x-4,_y+(_size_y/2)-5);
    gout << move_to(_x+_size_x-d+2,_y+(_size_y/2)+5) << line_to(_x+_size_x-1-(d/2),_y+_size_y-5) << line_to(_x+_size_x-4,_y+(_size_y/2)+5);
    gout << move_to(_x,_y) << text(std::to_string(num));
}

void SpinBox::handle(event ev)
{

}

int SpinBox::get_current_value()
{
    return num;
}

