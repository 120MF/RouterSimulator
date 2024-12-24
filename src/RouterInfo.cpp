#include "RouterInfo.h"

#include <iostream>
#include <gtkmm/stringlist.h>

RouterInfo::RouterInfo() {
    set_orientation(Gtk::Orientation::VERTICAL);

    const std::vector<Glib::ustring> strings{
        "1 minute", "2 minutes", "5 minutes", "20 minutes"
      };
    router_string_list = Gtk::StringList::create(strings);
    router_drop_down.set_model(router_string_list);
    router_drop_down.set_selected(0);

    router_drop_down.property_selected().signal_changed().connect(sigc::mem_fun(*this, &RouterInfo::on_dropdown_changed));

    append(router_drop_down);


}

void RouterInfo::on_dropdown_changed() {
    const auto selected = router_drop_down.get_selected();
    std::cout << "DropDown changed: Row=" << selected
      << ", String=" << router_string_list->get_string(selected) << std::endl;
}
