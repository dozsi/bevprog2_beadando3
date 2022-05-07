#ifndef WINDOW_H
#define WINDOW_H

#include "widget.h"

struct Window{
protected:
    std::vector<Widget *> widgets;
    int bamm;
public:
    Window();
    void event_loop();
    void registerwidget(Widget * w) {widgets.push_back(w);};
    void pass_values();
    void init();
};

#endif // WINDOW_H
