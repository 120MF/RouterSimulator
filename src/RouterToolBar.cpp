#include "RouterToolBar.h"

#include <iostream>
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


    append(button_new);
    append(button_erase);
}

void RouterToolBar::on_button_new_pressed() {
    auto parent = dynamic_cast<RouterActions*>(get_parent());
    if (parent) {
        parent->changeAction(IsUsingTool::AddRouter);
    }
}

void RouterToolBar::on_button_erase_pressed() {
    auto parent = dynamic_cast<RouterActions*>(get_parent());
    if (parent) {
        parent->changeAction(IsUsingTool::EraseRouter);
    }
}
