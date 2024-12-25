#ifndef ROUTERACTIONCONNECT_H
#define ROUTERACTIONCONNECT_H
#include <gtkmm/box.h>
#include <gtkmm/label.h>


struct RouterNode;
class RouterDrawingArea;

class RouterActionConnect : public Gtk::Box{
public:
    RouterActionConnect(RouterDrawingArea& area);
protected:
    void on_drawing_area_click(int, double, double);
    Gtk::Label label_;
private:
    RouterDrawingArea& area_;
    std::vector<RouterNode> two_nodes_;
};



#endif //ROUTERACTIONCONNECT_H
