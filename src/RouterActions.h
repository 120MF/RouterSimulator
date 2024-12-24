#ifndef ROUTERACTIONS_H
#define ROUTERACTIONS_H

#include <gtkmm/box.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

#include "RouterToolBar.h"

class RouterActionDefault : public Gtk::Box {
public:
    RouterActionDefault();
protected:
    Gtk::Label label;
};

class RouterActionAdd : public Gtk::Box {
public:
    RouterActionAdd();
protected:
    Gtk::Entry entry_name;
    Gtk::Entry entry_delay;
    Gtk::Label label;
    void on_entry_change();
};

class RouterActions : public Gtk::Box{
public:
    RouterActions();
    void changeAction(IsUsingTool tool);
protected:
    RouterToolBar tool_bar;

private:
    Gtk::Widget* current_widget;
};



#endif //ROUTERACTIONS_H
