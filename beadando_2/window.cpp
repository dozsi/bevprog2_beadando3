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
    gm.init();
    event_loop();
    white = false;
}
void Window::pass_values()
{
    for(int i = 0; i < widgets.size(); i++)
    {
        if (auto* pb = dynamic_cast<PushButton*>(widgets[i]))
        {
            if(pb->get_current_value()==true)
            {
                if(white && gm.set_state(i/8,i%8,'w'))
                {
                        white = false;
                }
                else if(gm.set_state(i/8,i%8,'b'))
                {
                        white = true;
                }
                pb->reset();
            }
        }
    }
}

void Window::paint(int focus)
{
    for(int i = 0; i <  widgets.size(); i++)
    {
        if (auto* pb = dynamic_cast<PushButton*>(widgets[i]))
        {
            if(gm.state_vector[i/8][i%8] == 'b')
                pb->set_current_text("X");
            if(gm.state_vector[i/8][i%8] == 'w')
                pb->set_current_text("O");
        }
    }
    for (Widget * w : widgets)
    {
        if(focus >= 0 && w == widgets[focus])
            w->draw(true);
        else
            w->draw(false);
    }
    gout << refresh;
}

void Window::event_loop()
{
    int focus = -1;
    paint(focus);
    event ev;
    while(gin >> ev  && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse && ev.button == btn_left)
            for (size_t i=0;i<widgets.size();i++)
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                    focus = i;
        if (focus!=-1)
            widgets[focus]->handle(ev);
        pass_values();
        paint(focus);
        gout << refresh;
    }
}

