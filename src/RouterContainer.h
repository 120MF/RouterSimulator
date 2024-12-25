#ifndef ROUTERAREA_H
#define ROUTERAREA_H

#include <gtkmm/frame.h>
#include <gtkmm/drawingarea.h>

#include "Router.h"

bool isPosInRect(const double &nodeX, const double &nodeY, const double& clickX, const double& clickY);


struct RouterNode {
    Router* router;
    double x,y;
    bool selected;
};

namespace Gtk {
    class GestureClick;
    class EventControllerMotion;
}

class RouterDrawingArea : public Gtk::DrawingArea {
public:
    RouterDrawingArea();
    Glib::RefPtr<Gtk::GestureClick> gesture_click;
protected:

    RouterNode* selected_node_;

    void on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int, int);
    void on_click(int n_press, double x, double y);
    void on_release(int, double, double);
    void on_motion(double x, double y);

    void draw_node(const Cairo::RefPtr<Cairo::Context>& cr, const RouterNode& node);
private:
    Glib::RefPtr<Gtk::EventControllerMotion> motion_controller_;
    Glib::RefPtr<Cairo::FtFontFace> font_face_;
};

class RouterContainer : public Gtk::Frame{
public:
    RouterContainer();
    ~RouterContainer() override;
    RouterDrawingArea area_;
protected:

};


#endif //ROUTERAREA_H
