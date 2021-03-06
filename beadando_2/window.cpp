#include "window.h"
#include "pushbutton.h"
#include "label.h"
#include "gamemaster.h"
#include <iostream>

using namespace std;
using namespace genv;

Window::Window() {}

void Window::init()
{
    gout.open(400,400);
    gout << font("LiberationSans-Regular.ttf",30);
    c = 'x';
    gm.init(c);
    end = false;
    event_loop();
}
void Window::pass_values()
{
    bool change = false;
    for(int i = 0; i < widgets.size(); i++)
    {
        if (auto* pb = dynamic_cast<PushButton*>(widgets[i]))
        {
            if(pb->get_current_value()==true)
            {
                if(c == 'o' && gm.set_state(i/8,i%8,'o'))
                {
                    c = 'x';
                }
                else if(gm.set_state(i/8,i%8,'x'))
                {
                    c = 'o';
                }
                change = true;
                pb->reset();
            }
        }
    }
    if(change)
    {
        if(gm.check_end(c))
        {
            if(c == 'o')
                c = 'x';
            else
                c = 'o';
            change = false;
        }
        if(!change && gm.check_end('o') && gm.check_end('x'))
        {
            end = true;
            cout << "O: " << gm.o_counter << " X: " << gm.x_counter <<  endl;
        }
    }
}


void Window::paint(int focus)
{
    if(end)
    {
        gout << color(0,0,0) << move_to(0,0) << box(400,400);
        if(gm.o_counter > gm.x_counter)
            gout << color(250,250,250) << move_to(150,200) << text("O nyert");
        else if (gm.o_counter < gm.x_counter)
            gout << color(250,250,250) << move_to(150,200) << text("X nyert");
        else
            gout << color(250,250,250) << move_to(150,200) << text("Dontetlen");
    }
    else
    {

        for(int i = 0; i <  widgets.size(); i++)
        {
            if (auto* pb = dynamic_cast<PushButton*>(widgets[i]))
            {
                if(gm.state_vector[i/8][i%8] == 'x')
                    pb->set_current_text("X");
                if(gm.state_vector[i/8][i%8] == 'o')
                    pb->set_current_text("O");
            }
        }
        for (int i = 0; i <  widgets.size(); i++)
        {
            if (auto* pb = dynamic_cast<PushButton*>(widgets[i]))
            {
                if(gm.state_vector[i/8][i%8] == 'a')
                {
                    pb->draw(1);
                }
                else if(gm.state_vector[i/8][i%8] == 'p')
                {
                    pb->draw(2);
                }
                else
                    pb->draw(0);
            }
        }
        if(end)
        {
            gout << color(0,0,0) << move_to(0,0) << box(400,400);
            if(gm.o_counter > gm.x_counter)
                gout << color(250,250,250) << move_to(150,200) << text("X nyert");
            else if (gm.o_counter < gm.x_counter)
                gout << color(250,250,250) << move_to(150,200) << text("O nyert");
            else
                gout << color(250,250,250) << move_to(150,200) << text("Dontetlen");
        }

        gm.check_end(c);
    }
    gout << refresh;
}

void Window::event_loop()
{
    int x;
    int y;
    int focus = -1;
    pass_values();
    paint(focus);
    event ev;
    while(gin >> ev  && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse && ev.pos_x >= 40 && ev.pos_y >= 40)
            for (size_t i=0;i<widgets.size();i++)
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                    x = ev.pos_y/40-1;
                    y = ev.pos_x/40-1;
                    gm.predict_state(x,y,c);
                }
        if (focus!=-1)
            widgets[focus]->handle(ev);
        pass_values();
        paint(focus);
    }
}

