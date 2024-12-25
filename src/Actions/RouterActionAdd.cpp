#include "RouterActionAdd.h"
#include "RouterContainer.h"
#include <iostream>
#include <gtkmm/gestureclick.h>

bool is_number(const Glib::ustring& s) {
    return !s.empty() && std::ranges::all_of(s, ::isdigit);
}

RouterActionAdd::RouterActionAdd(RouterDrawingArea &area) : area_(area) {
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
        drawing_area_connection_ = area_.gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &RouterActionAdd::on_drawing_area_click));
    }
    else {label.set_label("请输入路由器节点相关信息！"); drawing_area_connection_.disconnect();}
}

void RouterActionAdd::on_drawing_area_click(int,double,double) {
    std::cout << "click!!" << std::endl;
}