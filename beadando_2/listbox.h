#ifndef LISTBOX_H
#define LISTBOX_H

#include "widget.h"

class ListBox : public Widget {
protected:
    int current_text_index;
    int anchor;
    std::vector<std::string> string_vector;
    genv::canvas can;
    float slider_y_size;
    float slider_y;
    int start;
 public:
    ListBox(Window *w, int x, int y, int sx, int sy, std::vector<std::string> sv);
    virtual void draw(bool focused) override;
    virtual void handle(genv::event ev) override;
    std::string get_current_value();
    void move_elements(int value);
    void remove_element(std::string removed);
    void add_element(std::string added);
};

#endif // LISTBOX_H
