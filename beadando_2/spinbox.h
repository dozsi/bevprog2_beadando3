#ifndef SPINBOX_H
#define SPINBOX_H

#include "widget.h"

class SpinBox : public Widget {
protected:
    int num;
    int mini;
    int maxi;
public:
    SpinBox(Window *w, int x, int y, int sx, int sy, int min, int max);
    virtual void draw(bool focused) override;
    virtual void handle(genv::event ev) override;
    int get_current_value();
    void add(int n);
};

#endif // SPINBOX_H
