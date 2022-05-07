#ifndef LISTBOX_H
#define LISTBOX_H

#include "widget.h"

class ListBox : public Widget {
protected:
    std::string current_text;
 public:
    ListBox(Window *w, int x, int y, int sx, int sy, std::vector<std::string> wv);
    virtual void draw() override;
    virtual void draw_focused() override;
    virtual void handle(genv::event ev) override;
    std::string get_current_value();
};

#endif // LISTBOX_H
