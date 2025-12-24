#ifndef GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H
#define GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H

#include <QAction>
#include <QApplication>
#include <QCloseEvent>
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

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNew();
    void onOpen();
    bool onSave();
    bool onSaveAs();
    void documentWasModified();

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);

    QTextEdit *textEdit;
    QString currentFile;
};

#endif // GUI_WINDOWS_MAINWINDOW_MAINWINDOW_H