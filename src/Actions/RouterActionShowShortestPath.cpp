#include "RouterActionShowShortestPath.h"
#include "data_structure/Stack.h"

#include <gtkmm/gestureclick.h>

#include "NetworkManager.h"
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
                Glib::ustring label_str = "从路由器 " + another_node_->router->name() + " 到路由器 " + node->router->
                                          name() + "的最短路径：\n";
                const auto nm = NetworkManager::getInstance();
                while (!stack.isEmpty()) {
                    const auto router = stack.top();
                    const auto router_node = router_graph.getNode(router->hash(),
                                                                  [router](const std::shared_ptr<RouterNode> &node_) {
                                                                      if (node_->router.get() == router)
                                                                          return true;
                                                                      else return false;
                                                                  });
                    label_str += router->name();
                    label_str += " <- ";
                    router_node->onShortestPath = true;
                    stack.pop();
                }
                const uint32_t weight_sum = node->router->getShortestWeight(another_node_->router.get());
                another_node_ = nullptr;
                flag = false;
                label_str += "\n";
                label_str += "路线延迟（权重）总和: ";
                label_str += std::to_string(weight_sum);
                label_str += "\n请在图中选择两个路由器！";
                label_.set_label(label_str);
            } else {
                cleanupNodeBoolean();
                another_node_ = node;
                label_.set_label("已选中路由器: " + node->router->name() + " ；\n请再选择一个！");
            }
        }
    }, flag);
    area_.queue_draw();
}
