#include "RouterActionShowShortestPath.h"
#include "data_structure/Stack.h"

#include <gtkmm/gestureclick.h>

#include "RouterContainer.h"

extern Graph<std::shared_ptr<RouterNode>, uint16_t> router_graph;

RouterActionShowShortestPath::RouterActionShowShortestPath(RouterDrawingArea &area): area_(area) {
    label_.set_label("请在图中选择两个路由器！");
    append(label_);
    area_.gesture_click->signal_pressed().connect(
        sigc::mem_fun(*this, &RouterActionShowShortestPath::on_drawing_area_click));
}

void RouterActionShowShortestPath::cleanupNodeBoolean() {
    router_graph.visitAllNode([](const std::shared_ptr<RouterNode> &node) { node->onShortestPath = false; });
}

void RouterActionShowShortestPath::on_drawing_area_click(int, double x, double y) {
    bool flag = true;
    router_graph.visitAllNodeWhen([this,x,y,&flag](const std::shared_ptr<RouterNode> &node) {
        if (isPosInRect(node->x, node->y, x, y)) {
            if (another_node_.get()) {
                auto stack = node->router->getShortestPath(another_node_->router.get());
                while (!stack.isEmpty()) {
                    const auto router = stack.top();
                    const auto router_node = router_graph.getNode(router->hash(),
                                                                  [router](const std::shared_ptr<RouterNode> &node_) {
                                                                      if (node_->router.get() == router)
                                                                          return true;
                                                                      else return false;
                                                                  });
                    router_node->onShortestPath = true;
                    stack.pop();
                }
                another_node_ = nullptr;
                flag = false;
                label_.set_label("请在图中选择两个路由器！");
            } else {
                cleanupNodeBoolean();
                another_node_ = node;
                label_.set_label("已选中: " + node->router->get_name() + " 路由器；\n请再选择一个！");
            }
        }
    }, flag);
    area_.queue_draw();
}
