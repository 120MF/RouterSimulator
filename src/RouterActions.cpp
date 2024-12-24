#include <algorithm>
#include <cctype>
#include "RouterActions.h"

bool is_number(const Glib::ustring& s) {
    return !s.empty() && std::ranges::all_of(s, ::isdigit);
}

RouterActionDefault::RouterActionDefault() {
    label.set_label("请选择使用上方工具栏的工具！");
    append(label);
}

RouterActionAdd::RouterActionAdd() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_spacing(5);

    const auto label_name = Gtk::manage(new Gtk::Label("名称"));
    auto box1 = Gtk::manage(new Gtk::Box);
    box1->set_spacing(5);
    box1->set_orientation(Gtk::Orientation::HORIZONTAL);
    box1->append(*label_name);
    box1->append(entry_name);

    const auto label_delay = Gtk::manage(new Gtk::Label("延迟"));
    auto box2 = Gtk::manage(new Gtk::Box);
    box2->set_spacing(5);
    box2->set_orientation(Gtk::Orientation::HORIZONTAL);
    box2->append(*label_delay);
    box2->append(entry_delay);

    label.set_label("请输入路由器节点相关信息！");

    entry_name.signal_changed().connect(sigc::mem_fun(*this, &RouterActionAdd::on_entry_change));
    entry_delay.signal_changed().connect(sigc::mem_fun(*this, &RouterActionAdd::on_entry_change));

    append(*box1); append(*box2); append(label);

}

void RouterActionAdd::on_entry_change() {
    if (entry_name.get_text_length() && entry_delay.get_text_length() && is_number(entry_delay.get_text())) {
        label.set_label("在左侧图中点击生成路由器节点！");
    }
    else label.set_label("请输入路由器节点相关信息！");
}

RouterActions::RouterActions() {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_spacing(10);
    append(tool_bar);
    auto default_action = Gtk::manage(new RouterActionDefault);
    append(*default_action);
    current_widget = default_action;
}

void RouterActions::changeAction(IsUsingTool tool) {
    switch (tool) {
        case AddRouter: {
            auto routerAdder = Gtk::manage(new RouterActionAdd);
            remove(*current_widget);
            append(*routerAdder);
            current_widget = routerAdder;
            break;
        }
        default:
            break;
    }
}
