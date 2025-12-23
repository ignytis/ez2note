#ifndef GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H
#define GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QTextEdit>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
};

#endif // GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H