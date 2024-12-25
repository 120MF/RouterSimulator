#include "RouterActionErase.h"
#include "RouterContainer.h"

RouterActionErase::RouterActionErase(RouterDrawingArea &area):area_(area) {
    label_.set_label("点击删除图中路由器节点");
    append(label_);
}

void RouterActionErase::on_drawing_area_click(int, double, double) {
}
