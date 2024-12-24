#ifndef HELLOWORLD_H
#define HELLOWORLD_H
#include <gtkmm/window.h>
#include <gtkmm/box.h>

#include "RouterPaned.h"
#include "RouterContainer.h"

class MainWindow : public Gtk::Window
{

public:
    MainWindow();
    ~MainWindow() override;

protected:
    Gtk::Box vBox_;
    RouterContainer router_container;
    RouterPaned paned_widget;
};


#endif //HELLOWORLD_H
