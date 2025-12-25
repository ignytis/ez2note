#ifndef GUI_WINDOWS_MAINWINDOW_MAINWINDOW_HPP
#define GUI_WINDOWS_MAINWINDOW_MAINWINDOW_HPP

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

#include "../../../constants.hpp"
#include "../about/about.hpp"

/**
 * Main window which displays on start up
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    MainWindow(const QString &filePath, QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void onNew();
    void onOpen();
    bool onSave();
    bool onSaveAs();
    void documentWasModified();
    void onAbout();

private:
    bool maybeSave();
    void setCurrentFile(const QString &fileName);
    void openFile(const QString &filePath);

    QTextEdit *textEdit;
    QString currentFile;
};

#endif // GUI_WINDOWS_MAINWINDOW_MAINWINDOW_HPP