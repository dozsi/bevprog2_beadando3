#include "spinbox.h"
#include "listbox.h"
#include "window.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace genv;

struct W : public Window
{
    ListBox * l1;
    ListBox * l2;
    SpinBox * s1;
    SpinBox * s2;
    W()
    {
        l1 = new ListBox(this,10,120,150,250,{"egy","ket","ha","negy","ot","hat","het"});
        l2 = new ListBox(this,200,100,100,170,{"ez","itt","nagyon","sok","lehetoseg","annyira","hogy","el","sem","fer","egy","widgetben","gorgetes","nelkul"});
        s1 = new SpinBox(this,290,10,100,60,0,100);
        s1 = new SpinBox(this,60,55,150,30,1,20);
    }
    void save_values()
    {
        ofstream logfile("teszt.txt");
        for (Widget * wg : widgets)
        {
            if (auto* lb = dynamic_cast<ListBox*>(wg))
                logfile << lb->get_current_value() <<  endl;
            else if (auto* sb = dynamic_cast<SpinBox*>(wg))
               logfile << sb->get_current_value() <<  endl;
        }
        logfile.flush();
        logfile.close();
        cout << "logfile elmentve!" << endl;
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
            if (ev.type == ev_key && ev.keycode == key_enter)
                save_values();
            if (focus!=-1)
                widgets[focus]->handle(ev);
            for (Widget * w : widgets)
            {
                if(w == widgets[focus])
                    w->draw(true);
                else
                    w->draw(false);
            }
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
