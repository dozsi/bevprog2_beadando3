#ifndef WIDGET_H
#define WIDGET_H

#include <vector>
#include <variant>
#include "graphics.hpp"

struct Window;

class Widget {
protected:
    Window * _w;
    int _x, _y, _size_x, _size_y;
public:
    Widget(Window * w, int x, int y, int sx, int sy);
    virtual bool is_selected(int mouse_x, int mouse_y);
    virtual void draw() = 0;
    virtual void draw_focused() = 0;
    virtual void handle(genv::event ev) = 0;
};

#endif // WIDGET_H
