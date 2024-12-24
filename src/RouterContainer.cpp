#include "RouterContainer.h"

#include <iostream>
#include <cairomm/context.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/eventcontrollermotion.h>
RouterDrawingArea::RouterDrawingArea() : selected_node_(nullptr){
    set_size_request(400,200);
    gesture_click_ = Gtk::GestureClick::create();
    gesture_click_->signal_pressed().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_click));
    gesture_click_->signal_released().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_release));
    add_controller(gesture_click_);

    motion_controller_ = Gtk::EventControllerMotion::create();
    motion_controller_->signal_motion().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_motion));
    add_controller(motion_controller_);

    set_draw_func(sigc::mem_fun(*this, &RouterDrawingArea::on_draw));

    nodes_.push_back({100,100,false});
    nodes_.push_back({200,200,false});
}

RouterDrawingArea::~RouterDrawingArea() {
}

void RouterDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int,int) {
    cr->set_source_rgb(1.0, 1.0, 1.0);
    cr->paint();

    for (const auto& node : nodes_) {
        draw_node(cr,node);
    }
}

void RouterDrawingArea::on_click(int n_press, double x, double y) {
    std::cout << n_press << " " << x << " " << y << " " << std::endl;
    if (n_press >= 1) {
        for (auto& node: nodes_) {
            double dx = x - node.x;
            double dy = y - node.y;
            if (dx * dx + dy * dy <= 20 * 20) {
                node.selected = true;
                selected_node_ = &node;
                queue_draw();
                return;
            }
        }
    }
}

void RouterDrawingArea::on_release(int, double, double) {
    if (selected_node_) {
        selected_node_->selected = false;
        selected_node_ = nullptr;
        queue_draw();
    }
}

void RouterDrawingArea::on_motion(double x, double y) {
    if (selected_node_) {
        selected_node_->x = x;
        selected_node_->y = y;
        queue_draw();
    }
}
void RouterDrawingArea::draw_node(const Cairo::RefPtr<Cairo::Context> &cr, const RouterNode &node) {
    cr->save();
    cr->arc(node.x,node.y,20,0,2*M_PI);
    cr->set_source_rgb(node.selected ? 1.0 : 0.0,0.0,0.0);
    cr->fill_preserve();
    cr->set_source_rgb(0.0,0.0,0.0);
    cr->stroke();
    cr->restore();
}

RouterContainer::RouterContainer(): area_() {
    set_size_request(500,300);
    set_margin(10);
    set_label("路由器界面");
    set_label_align(Gtk::Align::START);
    set_child(area_);
}

RouterContainer::~RouterContainer() = default;
