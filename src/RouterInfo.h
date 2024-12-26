#ifndef ROUTERINFO_H
#define ROUTERINFO_H

#include <gtkmm/dropdown.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/stringlist.h>

class RouterInfo : public Gtk::Box{
public:
    RouterInfo();
    ~RouterInfo() override = default;
protected:
    void on_dropdown_changed();
    Gtk::DropDown router_drop_down;
    Gtk::Label label_router_name;
    Gtk::Label label_router_uuid;
    Gtk::Label label_router_delay;
    Glib::RefPtr<Gtk::StringList> router_string_list;
};

#endif //ROUTERINFO_H