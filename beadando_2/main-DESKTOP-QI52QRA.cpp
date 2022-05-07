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
        l1 = new ListBox(this,10,10,30,30,{"egy","ket","ha","negy","ot","hat"});
        l2 = new ListBox(this,10,50,40,40,{"alma","korte","barack"});
        s1 = new SpinBox(this,60,10,150,30,0,100);
        s1 = new SpinBox(this,60,50,150,30,1,10);
    }
    void save_values()
    {
        cout << "swaa:" << widgets.size() << endl;
        ofstream logfile("log.txt");
        int i;
        string s;
        for (Widget * wg : widgets)
        {

        }
        logfile.flush();
        logfile.close();
    }
};


int main()
{
    gout.open(400,400);
    gout  << font("LiberationSans-Regular.ttf",20);
    W w;
    w.save_values();
    w.event_loop();
    w.~W();
    return 0;
}
