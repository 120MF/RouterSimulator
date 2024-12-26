#include "RouterInfo.h"

#include <iostream>
#include <gtkmm/stringlist.h>
#include "RouterContainer.h"
extern Graph<std::shared_ptr<RouterNode>, uint16_t> router_graph;

Hashmap<Glib::ustring, std::shared_ptr<RouterNode>> node_map;

Glib::RefPtr<Gtk::StringList> router_string_list;

template<>
struct std::hash<Glib::ustring> {
    std::size_t operator()(const Glib::ustring &str) const noexcept {
        return std::hash<std::basic_string<char>>()(str.c_str());
    }
};

RouterInfo::RouterInfo() {
    set_orientation(Gtk::Orientation::VERTICAL);
    router_string_list = Gtk::StringList::create();
    router_graph.visitAllNode([this](std::shared_ptr<RouterNode>& node) {
        const Glib::ustring str = node->router->get_name();
        node_map.set(str, node);
        router_string_list->append(str);
    });
    const auto first_router = node_map.get(router_string_list->get_string(0))->router;
    label_router_name.set_label("Router Name: " + first_router->get_name());
    label_router_uuid.set_label("Router UUID: " + first_router->get_uuid());
    label_router_delay.set_label("Router Delay: " + std::to_string(first_router->delay()));

    router_drop_down.set_model(router_string_list);
    router_drop_down.set_selected(0);

    router_drop_down.property_selected().signal_changed().connect(sigc::mem_fun(*this, &RouterInfo::on_dropdown_changed));

    append(router_drop_down);
    append(label_router_name);
    append(label_router_uuid);
    append(label_router_delay);
}

void RouterInfo::NodeAdd(const std::shared_ptr<RouterNode> &node) {
    router_string_list->append(node->router->get_name());
    node_map.set(node->router->get_name(), node);
}

void RouterInfo::NodeErase(const std::shared_ptr<RouterNode> &node) {
    const Glib::ustring &name = node->router->get_name();
    for (int i = 0; i < router_string_list->get_n_items(); ++i) {
        if (router_string_list->get_string(i) == name) {
            router_string_list->remove(i);
            break;
        }
    }
    node_map.set(node->router->get_name(), node);
}

void RouterInfo::on_dropdown_changed() {
    const auto router = node_map.get(router_string_list->get_string(router_drop_down.get_selected()))->router;
    label_router_name.set_label("Router Name: " + router->get_name());
    label_router_uuid.set_label("Router UUID: " + router->get_uuid());
    label_router_delay.set_label("Router Delay: " + std::to_string(router->delay()));
}
