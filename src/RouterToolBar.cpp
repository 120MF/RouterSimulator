#include "RouterToolBar.h"
#include "RouterActions.h"

RouterToolBar::RouterToolBar() {
    set_margin(10);
    set_spacing(10);

    const auto label_open = Gtk::manage(new Gtk::Label("新建路由器"));
    button_new.set_child(*label_open);
    button_new.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_new_pressed));

    const auto label_erase = Gtk::manage(new Gtk::Label("删除路由器"));
    button_erase.set_child(*label_erase);
    button_erase.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_erase_pressed));

    const auto label_connect = Gtk::manage(new Gtk::Label("连接路由器"));
    button_connect.set_child(*label_connect);
    button_connect.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_connect_pressed));

    const auto label_show = Gtk::manage(new Gtk::Label("  最短路径  "));
    button_showShortestPath.set_child(*label_show);
    button_showShortestPath.signal_clicked().connect(sigc::mem_fun(*this, &RouterToolBar::on_button_show_pressed));


    append(button_new);
    append(button_erase);
    append(button_connect);
    append(button_showShortestPath);
}

void RouterToolBar::on_button_new_pressed() {
    if (const auto parent = dynamic_cast<RouterActions *>(get_parent())) {
        parent->changeAction(AddRouter);
    }
}

void RouterToolBar::on_button_erase_pressed() {
    if (const auto parent = dynamic_cast<RouterActions *>(get_parent())) {
        parent->changeAction(EraseRouter);
    }
}

void RouterToolBar::on_button_connect_pressed() {
    if (const auto parent = dynamic_cast<RouterActions *>(get_parent())) {
        parent->changeAction(ConnectRouter);
    }
}

void RouterToolBar::on_button_show_pressed() {
    if (const auto parent = dynamic_cast<RouterActions *>(get_parent())) {
        parent->changeAction(ShowShortestPath);
    }
}
