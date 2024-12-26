#include "RouterActionErase.h"
#include <gtkmm/gestureclick.h>

#include "NetworkManager.h"
#include "RouterContainer.h"
#include "RouterInfo.h"

extern Graph<std::shared_ptr<RouterNode>, uint16_t> router_graph;

RouterActionErase::RouterActionErase(RouterDrawingArea &area):area_(area) {
    label_.set_label("点击删除图中路由器节点");
    append(label_);
    area_.gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &RouterActionErase::on_drawing_area_click));
}

void RouterActionErase::on_drawing_area_click(int, const double x, const double y) {
    router_graph.visitAllNode([this,x,y](const std::shared_ptr<RouterNode>& node) {
        if (isPosInRect(node->x,node->y, x, y)) {
            router_graph.removeNode(node);
            RouterInfo::NodeErase(node);
            const auto nm = NetworkManager::getInstance();
            nm->removeRouter(node->router.get());
            area_.queue_draw();
        }
    });
}
