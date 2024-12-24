#include "RouterToolBar.h"

#include <iostream>
#include <gtkmm/image.h>

#include "RouterActions.h"

RouterToolBar::RouterToolBar() {
    auto icon_open = Gtk::manage(new Gtk::Image("document-open"));
    button_new.set_child(*icon_open);
    button_new.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_new_pressed));

    append(button_new);
}

void RouterToolBar::on_button_new_pressed() {
    auto parent = dynamic_cast<RouterActions*>(get_parent());
    if (parent) {
        parent->changeAction(IsUsingTool::AddRouter);
    }
}
