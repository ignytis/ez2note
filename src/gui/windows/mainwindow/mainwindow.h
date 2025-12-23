#ifndef GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H
#define GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H

#include <QAction>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QString>
#include <QTextEdit>

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