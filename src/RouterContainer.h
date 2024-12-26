#ifndef ROUTERAREA_H
#define ROUTERAREA_H

#include <functional>
#include <gtkmm/frame.h>
#include <gtkmm/drawingarea.h>

#include "Router.h"

bool isPosInRect(const double &nodeX, const double &nodeY, const double& clickX, const double& clickY);


struct RouterNode {
    RouterNode(Router* r, const double xPos, const double yPos, const bool sel) : router(r), x(xPos), y(yPos), selected(sel){}
    RouterNode(const RouterNode &other)
        : router(other.router),
          x(other.x),
          y(other.y),
          selected(other.selected) {
    }

    RouterNode(RouterNode &&other) noexcept
        : router(other.router),
          x(other.x),
          y(other.y),
          selected(other.selected) {
    }

    RouterNode & operator=(const RouterNode &other) {
        if (this == &other)
            return *this;
        router = other.router;
        x = other.x;
        y = other.y;
        selected = other.selected;
        return *this;
    }

    RouterNode & operator=(RouterNode &&other) noexcept {
        if (this == &other)
            return *this;
        router = other.router;
        x = other.x;
        y = other.y;
        selected = other.selected;
        return *this;
    }

    ~RouterNode(){delete router;}
    Router* router;
    double x,y;
    bool selected;
};

template<>
struct std::hash<RouterNode> {
    std::size_t operator()(const RouterNode &node) const noexcept {
        return static_cast<std::size_t>(node.router->hash());
    }
};

inline std::ostream &operator<<(std::ostream &os, const RouterNode &node) {
    os << node.router;
    return os;
}

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
