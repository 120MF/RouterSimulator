#include "RouterActionErase.h"
#include <gtkmm/gestureclick.h>
#include "RouterContainer.h"

extern std::vector<RouterNode> router_nodes;

RouterActionErase::RouterActionErase(RouterDrawingArea &area):area_(area) {
    label_.set_label("点击删除图中路由器节点");
    append(label_);
    area_.gesture_click->signal_pressed().connect(sigc::mem_fun(*this, &RouterActionErase::on_drawing_area_click));
}

void RouterActionErase::on_drawing_area_click(int, const double x, const double y) {
    for (auto it = router_nodes.begin(); it != router_nodes.end(); ++it) {
        if (isPosInRect(it->x, it->y, x, y)) {
            router_nodes.erase(it);
            break;
        }
    }
}
