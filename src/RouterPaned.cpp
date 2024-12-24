#include "RouterPaned.h"

RouterPaned::RouterPaned(RouterDrawingArea &area): router_actions(area) {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_margin(10);
    set_size_request(400, 600);
    set_start_child(router_info);
    set_end_child(router_actions);
}
