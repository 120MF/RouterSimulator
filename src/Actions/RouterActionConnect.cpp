#include "RouterActionConnect.h"
#include "RouterContainer.h"

RouterActionConnect::RouterActionConnect(RouterDrawingArea &area):area_(area) {
    label_.set_label("请在图中选择两个路由器！");
    append(label_);
}

void RouterActionConnect::on_drawing_area_click(int, double, double) {
}
