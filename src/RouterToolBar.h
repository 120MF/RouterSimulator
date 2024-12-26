#ifndef ROUTERTOOLBAR_H
#define ROUTERTOOLBAR_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>

class RouterToolBar : public Gtk::Box{
public:
    RouterToolBar();
protected:
    void on_button_new_pressed();
    void on_button_erase_pressed();
    void on_button_connect_pressed();
    void on_button_show_pressed();

    Gtk::Button button_new;
    Gtk::Button button_erase;
    Gtk::Button button_connect;
    Gtk::Button button_showShortestPath;

private:
};



#endif //ROUTERTOOLBAR_H
