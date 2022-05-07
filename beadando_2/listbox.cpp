#include "listbox.h"

using namespace genv;

ListBox::ListBox(Window *w, int x, int y, int sx, int sy, std::vector<std::string> wv)
    : Widget(w,x,y,sx,sy)
{
    current_text = wv[0];
}
void ListBox::draw()
{
    int c = 150;
    int d = 20;
    gout  << font("LiberationSans-Regular.ttf",20);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+_size_x-d,_y) << color(c,c,c) << line_to(_x+_size_x-d,_y+_size_y-2);
    gout << move_to(_x+_size_x-d,_y+(_size_y/2)) << color(c,c,c) << line_to(_x+_size_x-2,_y+(_size_y/2));
}
void ListBox::draw_focused()
{
    int c = 255;
    int d = 20;
    gout  << font("LiberationSans-Regular.ttf",20);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+_size_x-d,_y) << color(c,c,c) << line_to(_x+_size_x-d,_y+_size_y-2);
    gout << move_to(_x+_size_x-d,_y+(_size_y/2)) << color(c,c,c) << line_to(_x+_size_x-2,_y+(_size_y/2));
}

void ListBox::handle(event ev)
{

}

 std::string ListBox::get_current_value()
{
    return current_text;
}
