#include "RouterActionConnect.h"

#include <gtkmm/gestureclick.h>

#include "RouterContainer.h"

extern Graph<std::shared_ptr<RouterNode>, uint16_t> router_graph;

RouterActionConnect::RouterActionConnect(RouterDrawingArea &area):area_(area) {
    label_.set_label("请在图中选择两个路由器！");
    area_.gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &RouterActionConnect::on_drawing_area_click));
    append(label_);
}

void RouterActionConnect::on_drawing_area_click(int, double x, double y) {
    router_graph.visitAllNode([this,x,y](const std::shared_ptr<RouterNode>& node) {
        if (isPosInRect(node->x,node->y, x, y)) {
            if (another_node_.get()) {
                router_graph.addEdge(node, another_node_, node->router->delay() + another_node_->router->delay());
                another_node_ = nullptr;
                label_.set_label("请在图中选择两个路由器！");
            }
            else {
                another_node_ = node;
                label_.set_label("selected: " + node->router->get_name());
            }
        }
    });
}
