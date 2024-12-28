#include "RouterInfo.h"

#include <iostream>
#include <gtkmm/stringlist.h>
#include "RouterContainer.h"
extern Graph<std::shared_ptr<RouterNode>, uint16_t> router_graph;

Hashmap<Glib::ustring, std::shared_ptr<RouterNode> > node_map;

Glib::RefPtr<Gtk::StringList> router_string_list;

template<>
struct std::hash<Glib::ustring> {
    std::size_t operator()(const Glib::ustring &str) const noexcept {
        return std::hash<std::basic_string<char> >()(str.c_str());
    }
};

RouterInfo::RouterInfo() {
    router_string_list = Gtk::StringList::create();
    router_graph.visitAllNode([this](std::shared_ptr<RouterNode> &node) {
        const Glib::ustring str = node->router->name();
        node_map.set(str, node);
        router_string_list->append(str);
    });
    const auto first_router = node_map.get(router_string_list->get_string(0))->router;
    label_router_name.set_label("路由器名称: " + first_router->name());
    label_router_uuid.set_label("路由器 UUID: " + first_router->uuid());
    label_router_delay.set_label("路由器延迟: " + std::to_string(first_router->delay()));

    router_drop_down.set_model(router_string_list);
    router_drop_down.set_selected(0);

    router_drop_down.property_selected().signal_changed().connect(
        sigc::mem_fun(*this, &RouterInfo::on_dropdown_changed));
    auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL);
    box->append(router_drop_down);
    box->append(label_router_name);
    box->append(label_router_uuid);
    box->append(label_router_delay);

    set_label("路由器信息");
    set_child(*box);
}

void RouterInfo::NodeAdd(const std::shared_ptr<RouterNode> &node) {
    router_string_list->append(node->router->name());
    node_map.set(node->router->name(), node);
}

void RouterInfo::NodeErase(const std::shared_ptr<RouterNode> &node) {
    const Glib::ustring &name = node->router->name();
    for (int i = 0; i < router_string_list->get_n_items(); ++i) {
        if (router_string_list->get_string(i) == name) {
            router_string_list->remove(i);
            break;
        }
    }
    node_map.set(node->router->name(), node);
}

void RouterInfo::on_dropdown_changed() {
    const auto router = node_map.get(router_string_list->get_string(router_drop_down.get_selected()))->router;
    label_router_name.set_label("路由器名称: " + router->name());
    label_router_uuid.set_label("路由器 UUID: " + router->uuid());
    label_router_delay.set_label("路由器延迟: " + std::to_string(router->delay()));
}
