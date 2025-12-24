#ifndef GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H
#define GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QString>
#include <QTextEdit>

/**
 * Main window which displays on start up
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onNew();
    void onOpen();
    void onSave();

private:
    QTextEdit *textEdit;
    QString currentFile;
};

#endif // GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H