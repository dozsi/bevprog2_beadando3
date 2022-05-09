#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "widget.h"

class PushButton : public Widget {
protected:
    bool pushed;
    std::string txt;
public:
    PushButton(Window *w, int x, int y, int sx, int sy,std::string s);
    virtual void draw(bool focused) override;
    virtual void handle(genv::event ev) override;
    void draw(int focused);
    bool get_current_value();
    void reset();
    std::string get_current_text();
    void set_current_text(std::string s);
};

#endif // PUSHBUTTON_H
