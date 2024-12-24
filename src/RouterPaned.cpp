#include "RouterPaned.h"

RouterPaned::RouterPaned() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_margin(10);
    set_size_request(400,600);
    set_start_child(router_info);
    set_end_child(router_actions);
}
