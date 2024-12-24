#include "MainWindow.h"
#include "Router.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("tech.mfnest.routersimulator");

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<MainWindow>(argc, argv);
}