#include "RouterToolBar.h"
#include <gtkmm/image.h>
RouterToolBar::RouterToolBar() {
    auto icon_open = Gtk::manage(new Gtk::Image("document-open"));
    auto button_new = Gtk::manage(new Gtk::Button());
    button_new->set_child(*icon_open);
    // Gtk::Button button_erase;
    // Gtk::Button button_connect;
    // Gtk::Button button_showShortestPath;
    append(*button_new);
}
