#ifndef HELLOWORLD_H
#define HELLOWORLD_H
#include <gtkmm/window.h>
#include "RouterContainer.h"

class MainWindow : public Gtk::Window
{

public:
    MainWindow();
    ~MainWindow() override;

protected:
    RouterContainer router_container;
};


#endif //HELLOWORLD_H
