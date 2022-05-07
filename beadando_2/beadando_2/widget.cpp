#include "widget.h"
#include "window.h"
using namespace genv;

Widget::Widget(Window* w, int x, int y, int sx, int sy) :_w(w), _x(x), _y(y), _size_x(sx), _size_y(sy)
{
    w->registerwidget(this);
}

bool Widget::is_selected(int mouse_x, int mouse_y)
{
    return mouse_x>_x && mouse_x<_x+_size_x && mouse_y>_y && mouse_y<_y+_size_y;
}
