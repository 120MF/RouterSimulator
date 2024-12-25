#include "RouterActions.h"
#include "Actions/RouterActionAdd.h"

#include <iostream>
#include <gtkmm/gestureclick.h>

#include "Actions/RouterActionErase.h"

RouterActionDefault::RouterActionDefault() {
    label.set_label("请选择使用上方工具栏的工具！");
    append(label);
}

RouterActions::RouterActions(RouterDrawingArea &area):area_(area) {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_spacing(10);
    append(tool_bar);
    auto default_action = Gtk::manage(new RouterActionDefault);
    append(*default_action);
    current_widget = default_action;
}

void RouterActions::changeAction(IsUsingTool tool) {
    switch (tool) {
        case AddRouter: {
            auto routerAdder = Gtk::manage(new RouterActionAdd(area_));
            remove(*current_widget);
            append(*routerAdder);
            current_widget = routerAdder;
            break;
        }
        case EraseRouter: {
            auto routerEraser = Gtk::manage(new RouterActionErase(area_));
            remove(*current_widget);
            append(*routerEraser);
            current_widget = routerEraser;
            break;
        }
        default:
            break;
    }
}
