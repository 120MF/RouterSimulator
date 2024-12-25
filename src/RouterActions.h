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
