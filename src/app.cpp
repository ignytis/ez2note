#include "app.hpp"

App::App(int argc, char *argv[])
    : QApplication(argc, argv)
{
}

int App::exec()
{
    MainWindow window;
    window.resize(800, 600);
    window.show();
    return QApplication::exec();
}