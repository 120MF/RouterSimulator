#ifndef ROUTERACTIONSHOWSHORTESTPATH_H
#define ROUTERACTIONSHOWSHORTESTPATH_H
#include <gtkmm/box.h>
#include <gtkmm/label.h>

#include "RouterContainer.h"


class RouterDrawingArea;

class RouterActionShowShortestPath : public Gtk::Box {
public:
    explicit RouterActionShowShortestPath(RouterDrawingArea &area_);

    static void cleanupNodeBoolean();

protected:
    Gtk::Label label_;

    void on_drawing_area_click(int, double, double);

private:
    std::shared_ptr<RouterNode> another_node_;
    RouterDrawingArea &area_;
};


#endif //ROUTERACTIONSHOWSHORTESTPATH_H
