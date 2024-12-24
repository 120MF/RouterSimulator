#include "helloworld.h"
#include "Router.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.example");

    auto router = new Router();
    delete router;

    //Shows the window and returns when it is closed.
    return app->make_window_and_run<HelloWorld>(argc, argv);
}