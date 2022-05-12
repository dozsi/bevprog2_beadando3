#include "pushbutton.h"
#include "label.h"
#include "window.h"
#include <vector>
#include <iostream>

using namespace std;

struct W : public Window
{
    PushButton* pb;
    W()
    {
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 8; j++)
                pb = new PushButton(this,40+j*40,40+i*40,40,40,"");
    }
};

int main()
{
    ///minimax algoritmus
    W w;
    w.init();
    w.~W();
    return 0;
}
