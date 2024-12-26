#ifndef ROUTERINFO_H
#define ROUTERINFO_H

#include <gtkmm/dropdown.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/stringlist.h>

struct RouterNode;

class RouterInfo : public Gtk::Box{
public:
    RouterInfo();
    ~RouterInfo() override = default;
    static void NodeAdd(const std::shared_ptr<RouterNode> &node);
    static void NodeErase(const std::shared_ptr<RouterNode> &node);
protected:
    void on_dropdown_changed();
    Gtk::DropDown router_drop_down;
    Gtk::Label label_router_name;
    Gtk::Label label_router_uuid;
    Gtk::Label label_router_delay;
};

#endif //ROUTERINFO_H