#include "window.h"
#include "pushbutton.h"
#include "label.h"
#include <iostream>

using namespace std;
using namespace genv;

Window::Window() {}

void Window::init()
{
    gout.open(400,400);
    gout << font("LiberationSans-Regular.ttf",20);
    bamm = 0;
    event_loop();
}
void Window::pass_values()
{
    for (Widget * wg : widgets)
    {
        if (auto* pb = dynamic_cast<PushButton*>(wg))
        {
            if(pb->get_current_value()==true)
            {
                bamm = bamm * 10 + stoi(pb->get_current_text());
            }
            pb->reset();
        }

    }
    for (Widget * wg : widgets)
    {
        if (auto* lb = dynamic_cast<Label*>(wg))
        {
            lb->set_text(bamm);
        }
    }
}
void Window::event_loop()
{
    for (Widget * wg : widgets)
        wg->draw(false);
    gout << refresh;
    event ev;
    int focus = -1;
    while(gin >> ev  && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse && ev.button == btn_left)
            for (size_t i=0;i<widgets.size();i++)
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                    focus = i;
        if (focus!=-1)
            widgets[focus]->handle(ev);
        pass_values();
        for (Widget * w : widgets)
        {
            if(w == widgets[focus])
                w->draw(true);
            else
                w->draw(false);
        }
        gout << refresh;
    }
}

