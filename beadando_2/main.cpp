#include "pushbutton.h"
#include "label.h"
#include "window.h"

struct W : public Window
{
    Label * l1;
    PushButton * p1;
    W()
    {
        l1 = new Label(this,10,30,150,30,0);
        p1 = new PushButton(this,10,70,30,30,"1");
    }
};

int main()
{
    W w;
    w.init();
    w.~W();
    return 0;
}
