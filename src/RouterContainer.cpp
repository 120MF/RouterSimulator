#include "RouterContainer.h"

#include <iostream>
#include <cairomm/context.h>
#include <cairomm/fontface.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/eventcontrollermotion.h>

std::vector<RouterNode> router_nodes;

constexpr double RECT_WIDTH = 60;
constexpr double RECT_HEIGHT = 40;

RouterDrawingArea::RouterDrawingArea() : selected_node_(nullptr){
    gesture_click = Gtk::GestureClick::create();
    gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_click));
    gesture_click->signal_released().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_release));
    add_controller(gesture_click);

    motion_controller_ = Gtk::EventControllerMotion::create();
    motion_controller_->signal_motion().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_motion));
    add_controller(motion_controller_);

    set_draw_func(sigc::mem_fun(*this, &RouterDrawingArea::on_draw));

    router_nodes.push_back({new Router("1"),100,100,false});
    router_nodes.push_back({new Router("2"),200,200,false});
}


void RouterDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int,int) {
    cr->set_source_rgb(1,1,1);
    cr->paint();
    for (const auto& node : router_nodes) {
        draw_node(cr,node);
    }
}

void RouterDrawingArea::on_click(int n_press, double x, double y) {
    std::cout << n_press << " " << x << " " << y << " " << std::endl;
    if (n_press >= 1) {
        for (auto& node: router_nodes) {
            double dx = x - node.x;
            double dy = y - node.y;
            if (dx >= -RECT_WIDTH / 2 && dx <= RECT_WIDTH / 2 && dy >= -RECT_HEIGHT / 2 && dy <= RECT_HEIGHT / 2) {
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

    // Draw rectangle

    cr->rectangle(node.x - RECT_WIDTH / 2, node.y - RECT_HEIGHT / 2, RECT_WIDTH, RECT_HEIGHT);
    cr->set_source_rgb(node.selected ? 1.0 : 0.5, 0.0, 0.3);
    cr->fill_preserve();
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->stroke();

    // Draw text
    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->select_font_face("Sans",Cairo::ToyFontFace::Slant::NORMAL,Cairo::ToyFontFace::Weight::NORMAL);
    cr->set_font_size(12);
    Cairo::TextExtents extents;
    cr->get_text_extents(node.router->get_name(), extents);
    cr->move_to(node.x - extents.width / 2, node.y + extents.height / 2);
    cr->show_text(node.router->get_name());

    cr->restore();
}

RouterContainer::RouterContainer(): area_() {
    set_size_request(500,300);
    set_margin(10);
    set_label("路由器界面");
    set_label_align(Gtk::Align::START);
    set_child(area_);
}

RouterContainer::~RouterContainer() {
    for (const auto & node : router_nodes) {
        delete node.router;
    }
}
