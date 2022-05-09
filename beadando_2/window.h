#ifndef WINDOW_H
#define WINDOW_H
#include "gamemaster.h"
#include "widget.h"

struct Window{
protected:
    std::vector<Widget *> widgets;
    GameMaster gm;
    bool white;
public:
    Window();
    void event_loop();
    void registerwidget(Widget * w) {widgets.push_back(w);};
    void pass_values();
    void init();
    void paint(int focus);
};

#endif // WINDOW_H
