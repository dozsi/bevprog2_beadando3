#include "spinbox.h"
#include "listbox.h"
#include "pushbutton.h"
#include "label.h"
#include "window.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace genv;

struct W : public Window
{
    int bamm;
    Label * l1;
    PushButton * p0;
    PushButton * p1;
    PushButton * p2;
    PushButton * p3;
    PushButton * p4;
    PushButton * p5;
    PushButton * p6;
    PushButton * p7;
    PushButton * p8;
    PushButton * p9;
    PushButton * p10;
    PushButton * p11;
    PushButton * p12;
    PushButton * p13;
    PushButton * p14;
    W()
    {
        l1 = new Label(this,10,30,150,30,0);
        p0 = new PushButton(this,50,190,30,30,"0");
        p1 = new PushButton(this,10,70,30,30,"1");
        p2 = new PushButton(this,50,70,30,30,"2");
        p3 = new PushButton(this,90,70,30,30,"3");
        p4 = new PushButton(this,10,110,30,30,"4");
        p5 = new PushButton(this,50,110,30,30,"5");
        p6 = new PushButton(this,90,110,30,30,"6");
        p7 = new PushButton(this,10,150,30,30,"7");
        p8 = new PushButton(this,50,150,30,30,"8");
        p9 = new PushButton(this,90,150,30,30,"9");
        p10 = new PushButton(this,130,70,30,30,"+");
        p11 = new PushButton(this,130,110,30,30,"-");
        p12 = new PushButton(this,130,150,30,30,"*");
        p13 = new PushButton(this,130,190,30,30,"/");
        p14 = new PushButton(this,90,190,30,30,"=");
    }
    void pass_values()
    {
        bool ev = false;
        for (Widget * wg : widgets)
        {
            if (auto* pb = dynamic_cast<PushButton*>(wg))
            {
                if(pb->get_current_value()==true)
                {
                    bamm = bamm * 10 + stoi(pb->get_current_text());
                    cout << pb->get_current_value() << endl;
                }
                pb->reset();
                ev = true;
            }
        }
        if(ev)
            l1->set_text(bamm);
    }
    void event_loop()
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
            for (Widget * w : widgets)
            {
                if(w == widgets[focus])
                    w->draw(true);
                else
                    w->draw(false);
            }
            pass_values();
            gout << refresh;
        }
        return;
    }
};

int main()
{
    gout.open(400,400);
    gout  << font("LiberationSans-Regular.ttf",20);
    W w;
    w.event_loop();
    w.~W();
    return 0;
}
