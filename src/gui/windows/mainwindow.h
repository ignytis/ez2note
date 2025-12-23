#ifndef GUI_WINDOWS_MAINWINDOW_H
#define GUI_WINDOWS_MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QMenuBar>
#include <QMenu>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
};

#endif // GUI_WINDOWS_MAINWINDOW_H