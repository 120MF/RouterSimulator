#ifndef ROUTERTOOLBAR_H
#define ROUTERTOOLBAR_H

#include <gtkmm/box.h>
#include <gtkmm/button.h>

enum IsUsingTool {
    AddRouter = 1,
    EraseRouter = 2,
    ConnectRouter = 3,
    ShowShortestPath = 4,
};

class RouterToolBar : public Gtk::Box{
public:
    RouterToolBar();
protected:
    void on_button_new_pressed();
    void on_button_erase_pressed();

    Gtk::Button button_new;
    Gtk::Button button_erase;
    Gtk::Button button_connect;
    Gtk::Button button_showShortestPath;

private:
    IsUsingTool status_;

public:
    [[nodiscard]] IsUsingTool status() const {
        return status_;
    }

    void set_status(IsUsingTool status) {
        this->status_ = status;
    }
};



#endif //ROUTERTOOLBAR_H
