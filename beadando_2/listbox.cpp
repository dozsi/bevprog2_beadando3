#include "listbox.h"
using namespace genv;
using namespace std;

int e = 20;
ListBox::ListBox(Window *w, int x, int y, int sx, int sy, std::vector<std::string> sv)
    : Widget(w,x,y,sx,sy)
{
    current_text_index = 0;
    anchor = 0;
    string_vector = sv;
    slider_y = _y+e-4;
    slider_y_size = (_size_y-e-e+9)*(_size_y-e-e+9)/(sv.size()*e);
    if(slider_y_size > _size_y-2*e)
        slider_y_size = _size_y-e-e+9;
}

void ListBox::draw(bool focused)
{
    can.open(_size_x,(string_vector.size()+1)*e);
    can << move_to(0,0) << color(0,0,0) << box(_size_x,(string_vector.size()+1)*e);
    int c = 150;
    int b = 50;
    if(focused)
    {
        c = 255;
        b = 100;
    }
    gout  << font("LiberationSans-Regular.ttf",e);
    gout << move_to(_x, _y) << color(c,c,c) << box(_size_x, _size_y);
    gout << move_to(_x+2, _y+2) << color(0,0,0) << box(_size_x-4, _size_y-4);
    gout << move_to(_x+_size_x-e,_y) << color(c,c,c) << line_to(_x+_size_x-e,_y+_size_y-2);
    ///vertical lines
    gout << move_to(_x+_size_x-e,_y+e/2+5) << line_to(_x+_size_x-2,_y+e/2+5);
    gout << move_to(_x+_size_x-e,_y+_size_y-e/2-5) << line_to(_x+_size_x-2,_y+_size_y-e/2-5);
    ///arrows
    gout << move_to(_x+_size_x-e+2,_y+e/2) << line_to(_x+_size_x-1-(e/2),_y+5) << line_to(_x+_size_x-4,_y+e/2);
    gout << move_to(_x+_size_x-e+2,_y+_size_y-e/2) << line_to(_x+_size_x-1-(e/2),_y+_size_y-5) << line_to(_x+_size_x-4,_y+_size_y-e/2);
    ///slider
    gout << color(c-b,c-b,c-b) << move_to(_x+_size_x-e+1,slider_y) << box(e-2,slider_y_size);
    for (int i = 0; i < string_vector.size(); i++)
    {
        if(current_text_index == i)
            can << color(b,b,b)<<move_to(0,i*e) << box(_size_x-e-2,e);
        can << color(c,c,c)<<move_to(4,gout.cascent()+gout.cdescent()+i*e) << text(string_vector[i]);
    }
    gout << stamp(can, 0, anchor, _size_x-e-2, _size_y-4, _x+2, _y+2);
}

void ListBox::move_elements(int value)
{
    anchor+=value;
    if(anchor+_size_y >= string_vector.size()*e+e/4)
        anchor = string_vector.size()*e+e/4-_size_y;
    if(anchor < 0 || _size_y > string_vector.size()*e)
        anchor = 0;
    slider_y += value;//*(_size_y-e-e+9)/(string_vector.size()*e);
    if(slider_y < _y+e-4)
        slider_y = _y+e-4;
    if(slider_y > _y+_size_y-e+5-slider_y_size)
        slider_y = _y+_size_y-e+5-slider_y_size;
}

void ListBox::handle(event ev)
{
    if(ev.pos_x > _x+_size_x-e   && ev.pos_x <= _x+_size_x && ev.type == ev_mouse) ///side
    {
        if(ev.pos_y >= _y+_size_y-e/2-5  && ev.button < 0 && ev.type == ev_mouse) ///down
            move_elements(5);
        if(ev.pos_y <= _y+e/2+5  && ev.button < 0 && ev.type == ev_mouse) ///up
            move_elements(-5);
        if(ev.pos_y > _y+e/2+5 && ev.pos_y < _y+_size_y-e/2-5 && ev.button > 0 && ev.type == ev_mouse)///slider
        {
            if(ev.pos_y < slider_y)///over slider
            {
                move_elements(-10);
                start = 0;
            }
            else if(ev.pos_y > slider_y+slider_y_size)///under slider
            {
                move_elements(10);
                start = 0;
            }
            else///slider
            {
                start = ev.pos_y;
            }
        }
        else if(start != 0 && ev.button < 0 && ev.type == ev_mouse)
        {
            move_elements((ev.pos_y-start)*(_size_y/(_size_y-e-10)));
            start = 0;
        }
    }
    else if(ev.pos_x < _x+_size_x-e && ev.pos_x > _x && ev.button < 0 && ev.type == ev_mouse)///mid
        current_text_index = (ev.pos_y-_y-3+anchor)/e;
}

void ListBox::remove_element(std::string removed)
{
    for(int i = 0; i < string_vector.size(); i++)
    {
        if(string_vector[i] == removed)
        {
            string_vector.erase(string_vector.begin() + i);
            break;
        }
    }
}

void ListBox::add_element(std::string added)
{
    string_vector.push_back(added);
}

std::string ListBox::get_current_value()
{
    return string_vector[current_text_index];
}
