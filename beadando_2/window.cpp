#include "window.h"
#include <iostream>
using namespace genv;

Window::Window() {}
void Window::event_loop() {
    for (Widget * wg : widgets)
    {
        wg->draw();
    }
    gout << refresh;
    event ev;
    int focus = -1;
    while(gin >> ev  && ev.keycode != key_escape)
    {
        if (ev.type == ev_mouse && ev.button == btn_left)
        {
            for (size_t i=0;i<widgets.size();i++)
            {
                if (widgets[i]->is_selected(ev.pos_x, ev.pos_y))
                {
                    focus = i;
                }
            }
        }
        if (focus!=-1)
        {
            widgets[focus]->handle(ev);
        }
        for (Widget * w : widgets)
        {
            if(w == widgets[focus])
                w->draw_focused();
            else
                w->draw();
        }
        gout << refresh;
        //gout << move_to(0,0) << color(0,0,0) << box(400,400);
    }
    return;
}
