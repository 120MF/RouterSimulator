#ifndef ROUTERACTIONS_H
#define ROUTERACTIONS_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

#include "RouterToolBar.h"

class RouterDrawingArea;

class RouterActionDefault : public Gtk::Box {
public:
    RouterActionDefault();
protected:
    Gtk::Label label;
};

class RouterActionAdd : public Gtk::Box {
public:
    RouterActionAdd(RouterDrawingArea& area);
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

class RouterActions : public Gtk::Box{
public:
    RouterActions(RouterDrawingArea &area);
    void changeAction(IsUsingTool tool);
protected:
    RouterToolBar tool_bar;

private:
    Gtk::Widget* current_widget;
    RouterDrawingArea &area_;
};



#endif //ROUTERACTIONS_H
