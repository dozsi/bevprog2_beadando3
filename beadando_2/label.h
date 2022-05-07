#ifndef LABEL_H
#define LABEL_H

#include "widget.h"

class Label : public Widget {
protected:
    int txt;
 public:
    Label(Window *w, int x, int y, int sx, int sy, int s);
    virtual void draw(bool focused) override;
    virtual void handle(genv::event ev) override;
    int get_current_value();
    void set_text(int);
};

#endif // LABEL_H
