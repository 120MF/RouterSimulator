#include "MainWindow.h"
#include <iostream>

MainWindow::MainWindow()
{
    set_title("RouterSimulator");
    set_default_size(800,600);
    set_child(router_container);
}

MainWindow::~MainWindow()
{
}