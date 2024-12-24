#ifndef ROUTERACTIONS_H
#define ROUTERACTIONS_H

#include <gtkmm/box.h>

#include "RouterToolBar.h"

class RouterActions : public Gtk::Box{
public:
    RouterActions();
protected:
    RouterToolBar tool_bar;

};



#endif //ROUTERACTIONS_H
