#ifndef ROUTERACTIONERASE_H
#define ROUTERACTIONERASE_H
#include <gtkmm/box.h>
#include <gtkmm/label.h>


class RouterDrawingArea;

class RouterActionErase : public Gtk::Box{
public:
    explicit RouterActionErase(RouterDrawingArea& area);
protected:
    Gtk::Label label_;
    void on_drawing_area_click(int, double, double);
private:
    RouterDrawingArea& area_;
};



#endif //ROUTERACTIONERASE_H
