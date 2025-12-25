#ifndef APP_H
#define APP_H

#include <QApplication>
#include <QCommandLineParser>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QTextEdit>

#include "constants.hpp"
#include "gui/windows/mainwindow/mainwindow.hpp"

/**
 * Main class of application
 */
class App: public QApplication
{
public:
    App(int argc, char *argv[]);

    int exec();
};

#endif // APP_H