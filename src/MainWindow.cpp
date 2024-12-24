#include "MainWindow.h"

MainWindow::MainWindow():paned_widget(router_container.area_) {
    set_title("RouterSimulator");
    set_decorated(true);

    vBox_.set_orientation(Gtk::Orientation::HORIZONTAL);
    vBox_.append(router_container);
    vBox_.append(paned_widget);
    set_child(vBox_);
}

MainWindow::~MainWindow()
{
}
