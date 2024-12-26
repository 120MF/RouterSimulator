#include "RouterToolBar.h"

#include <gtkmm/image.h>

#include "RouterActions.h"

RouterToolBar::RouterToolBar() {
    set_margin(10);
    set_spacing(5);

    auto icon_open = Gtk::manage(new Gtk::Image("document-open"));
    button_new.set_child(*icon_open);
    button_new.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_new_pressed));

    auto icon_erase = Gtk::manage(new Gtk::Image("icon-erase"));
    button_erase.set_child(*icon_erase);
    button_erase.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_erase_pressed));

    auto icon_connect = Gtk::manage(new Gtk::Image("icon-connect"));
    button_connect.set_child(*icon_connect);
    button_connect.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_connect_pressed));

    auto icon_show = Gtk::manage(new Gtk::Image("icon-show"));
    button_showShortestPath.set_child(*icon_show);
    button_showShortestPath.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_show_pressed));



    append(button_new);
    append(button_erase);
    append(button_connect);
    append(button_showShortestPath);
}

void RouterToolBar::on_button_new_pressed() {
    if (const auto parent = dynamic_cast<RouterActions*>(get_parent())) {
        parent->changeAction(AddRouter);
    }
}

void RouterToolBar::on_button_erase_pressed() {
    if (const auto parent = dynamic_cast<RouterActions*>(get_parent())) {
        parent->changeAction(EraseRouter);
    }
}

void RouterToolBar::on_button_connect_pressed() {
    if (const auto parent = dynamic_cast<RouterActions*>(get_parent())) {
        parent->changeAction(ConnectRouter);
    }
}

void RouterToolBar::on_button_show_pressed() {
    if (const auto parent = dynamic_cast<RouterActions*>(get_parent())) {
        parent->changeAction(ShowShortestPath);
    }
}
