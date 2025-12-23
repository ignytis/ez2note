#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    // Set window title
    setWindowTitle("ez2note");

    // Create a text edit widget
    QTextEdit *textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    // Create a menu bar
    QMenuBar *menuBar = new QMenuBar;
    setMenuBar(menuBar);

    // Create a File menu
    QMenu *fileMenu = menuBar->addMenu("File");

    // Add actions to the File menu (e.g., New, Open, Save, Exit)
    fileMenu->addAction("New");
    fileMenu->addAction("Open");
    fileMenu->addAction("Save");
    fileMenu->addSeparator();
    fileMenu->addAction("Exit");
}