#include "RouterActions.h"
#include "Actions/RouterActionAdd.h"

#include <iostream>
#include <gtkmm/gestureclick.h>

#include "Actions/RouterActionConnect.h"
#include "Actions/RouterActionErase.h"
#include "Actions/RouterActionShowShortestPath.h"

RouterActionDefault::RouterActionDefault() {
    label.set_label("请选择使用上方工具栏的工具！");
    append(label);
}

RouterActions::RouterActions(RouterDrawingArea &area): area_(area) {
    set_orientation(Gtk::Orientation::VERTICAL);
    set_spacing(10);
    append(tool_bar);
    auto default_action = Gtk::manage(new RouterActionDefault);
    append(*default_action);
    current_widget = default_action;
}

void RouterActions::changeAction(UsingAction tool) {
    if (status_ == ShowShortestPath) {
    }
    switch (tool) {
        case AddRouter: {
            auto routerAdder = Gtk::manage(new RouterActionAdd(area_));
            remove(*current_widget);
            append(*routerAdder);
            current_widget = routerAdder;
            status_ = AddRouter;
            break;
        }
        case EraseRouter: {
            auto routerEraser = Gtk::manage(new RouterActionErase(area_));
            remove(*current_widget);
            append(*routerEraser);
            current_widget = routerEraser;
            status_ = EraseRouter;
            break;
        }
        case ConnectRouter: {
            auto routerConnector = Gtk::manage(new RouterActionConnect(area_));
            remove(*current_widget);
            append(*routerConnector);
            current_widget = routerConnector;
            status_ = ConnectRouter;
            break;
        }
        case ShowShortestPath: {
            auto routerPathfinder = Gtk::manage(new RouterActionShowShortestPath(area_));
            remove(*current_widget);
            append(*routerPathfinder);
            current_widget = routerPathfinder;
            status_ = ShowShortestPath;
            break;
        }
        default:
            break;
    }
}
