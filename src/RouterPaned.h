#ifndef PANEDWIDGET_H
#define PANEDWIDGET_H

#include <gtkmm/paned.h>

#include "RouterActions.h"
#include "RouterInfo.h"

class RouterDrawingArea;

class RouterPaned :public Gtk::Paned{
public:
    RouterPaned(RouterDrawingArea &area);
    ~RouterPaned() override = default;
protected:
    RouterInfo router_info;
    RouterActions router_actions;

};



#endif //PANEDWIDGET_H
