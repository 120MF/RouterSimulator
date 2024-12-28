#include "RouterContainer.h"
#include "data_structure/Graph.h"
#include <cairomm/context.h>
#include <cairomm/fontface.h>
#include <gtkmm/gestureclick.h>
#include <gtkmm/eventcontrollermotion.h>

#include "NetworkManager.h"

Graph<std::shared_ptr<RouterNode>, uint16_t> router_graph;

constexpr double RECT_WIDTH = 60;
constexpr double RECT_HEIGHT = 40;

bool isPosInRect(const double &nodeX, const double &nodeY, const double &clickX, const double &clickY) {
    const double dx = clickX - nodeX;
    const double dy = clickY - nodeY;
    if (dx >= -RECT_WIDTH / 2 && dx <= RECT_WIDTH / 2 && dy >= -RECT_HEIGHT / 2 && dy <= RECT_HEIGHT / 2) return true;
    return false;
}

RouterDrawingArea::RouterDrawingArea() : selected_node_(nullptr) {
    gesture_click = Gtk::GestureClick::create();
    gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_click));
    gesture_click->signal_released().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_release));
    add_controller(gesture_click);

    motion_controller_ = Gtk::EventControllerMotion::create();
    motion_controller_->signal_motion().connect(sigc::mem_fun(*this, &RouterDrawingArea::on_motion));
    add_controller(motion_controller_);

    set_draw_func(sigc::mem_fun(*this, &RouterDrawingArea::on_draw));

    const auto node1 = std::make_shared<RouterNode>(RouterNode{std::make_shared<Router>("1"), 100, 100, false});
    const auto node2 = std::make_shared<RouterNode>(RouterNode{std::make_shared<Router>("2"), 200, 200, false});

    router_graph.addNode(node1);
    router_graph.addNode(node2);
    router_graph.addEdge(node1, node2, node1->router->delay() + node2->router->delay());

    const auto nm = NetworkManager::getInstance();

    nm->addRouter(node1->router.get());
    nm->addRouter(node2->router.get());
    nm->connect(node1->router.get(), node2->router.get());
}


void RouterDrawingArea::on_draw(const Cairo::RefPtr<Cairo::Context> &cr, int, int) {
    cr->set_source_rgb(0.94509804, 0.98039216, 0.93333333);
    cr->paint();
    router_graph.visitAllNode([&cr, this](std::shared_ptr<RouterNode> &node) {
        router_graph.visitAllEdge(node, [&cr,node,this](const std::shared_ptr<RouterNode> &node_v, uint16_t) {
            draw_edge(cr, node, node_v);
        });
    });
    router_graph.visitAllNode([&cr,this](std::shared_ptr<RouterNode> &node) {
        draw_node(cr, node);
    });
}

void RouterDrawingArea::on_click(int n_press, double x, double y) {
    router_graph.visitAllNode([this, x, y](const std::shared_ptr<RouterNode> &node) {
        if (isPosInRect(node->x, node->y, x, y)) {
            node->selected = true;
            selected_node_ = node.get();
            queue_draw();
        }
    });
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

void RouterDrawingArea::draw_node(const Cairo::RefPtr<Cairo::Context> &cr, const std::shared_ptr<RouterNode> node) {
    cr->save();

    cr->rectangle(node->x - RECT_WIDTH / 2, node->y - RECT_HEIGHT / 2, RECT_WIDTH, RECT_HEIGHT);
    if (selected_node_ == node.get()) cr->set_source_rgb(0.90196078, 0.22352941, 0.27450980);
    else cr->set_source_rgb(0.65882353, 0.85490196, 0.86274510);
    cr->fill_preserve();

    if (node->onShortestPath)
        cr->set_source_rgb(0.8, 0.2, 0.2);
    else
        cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->stroke();

    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->select_font_face("Sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
    cr->set_font_size(12);
    Cairo::TextExtents extents;
    cr->get_text_extents(node->router->name(), extents);
    cr->move_to(node->x - extents.width / 2, node->y + extents.height / 2);
    cr->show_text(node->router->name());

    const std::string delay_s = std::to_string(node->router->delay());
    cr->get_text_extents(delay_s, extents);
    cr->move_to(node->x - extents.width / 2, node->y + RECT_HEIGHT);
    cr->show_text(delay_s);

    cr->restore();
}

void RouterDrawingArea::draw_edge(const Cairo::RefPtr<Cairo::Context> &cr, std::shared_ptr<RouterNode> node_s,
                                  std::shared_ptr<RouterNode> node_v) {
    cr->save();
    if (node_s->onShortestPath && node_v->onShortestPath)
        cr->set_source_rgb(0.90196078, 0.22352941, 0.27450980);
    else cr->set_source_rgb(0.0, 0.0, 0.0);

    cr->move_to(node_s->x, node_s->y);
    cr->line_to(node_v->x, node_v->y);
    cr->stroke();

    const double mid_x = (node_s->x + node_v->x) / 2;
    const double mid_y = (node_s->y + node_v->y) / 2;

    const uint32_t weight = router_graph.getEdgeWeight(node_s, node_v);

    cr->set_source_rgb(0.0, 0.0, 0.0);
    cr->select_font_face("Sans", Cairo::ToyFontFace::Slant::NORMAL, Cairo::ToyFontFace::Weight::NORMAL);
    cr->set_font_size(10);
    Cairo::TextExtents extents;
    const std::string weight_text = std::to_string(weight);

    cr->get_text_extents(weight_text, extents);
    cr->move_to(mid_x, mid_y - extents.height);
    cr->show_text(weight_text);

    cr->restore();
}


RouterContainer::RouterContainer(): area_() {
    set_size_request(500, 300);
    set_margin(10);
    set_label("路由器界面");
    set_label_align(Gtk::Align::START);
    set_child(area_);
}

RouterContainer::~RouterContainer() {
}
