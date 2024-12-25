#ifndef ROUTERACTIONADD_H
#define ROUTERACTIONADD_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

class RouterDrawingArea;

class RouterActionAdd : public Gtk::Box {
public:
    explicit RouterActionAdd(RouterDrawingArea& area);
protected:
    Gtk::Entry entry_name;
    Gtk::Entry entry_delay;
    Gtk::Label label;
    void on_entry_change();
    void on_drawing_area_click(int,double,double);
private:
    sigc::connection drawing_area_connection_;
    RouterDrawingArea& area_;
};

#endif //ROUTERACTIONADD_H
