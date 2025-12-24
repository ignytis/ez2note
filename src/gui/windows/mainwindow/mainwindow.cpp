#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Set window title
    setWindowTitle("ez2note");

    // Create a text edit widget
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    // Create a menu bar
    QMenuBar *menuBar = new QMenuBar;
    setMenuBar(menuBar);

    // Create a File menu
    QMenu *fileMenu = menuBar->addMenu("File");

    // Add actions to the File menu (e.g., New, Open, Save, Exit)
    QAction *newAction = fileMenu->addAction("New");
    QAction *openAction = fileMenu->addAction("Open");
    QAction *saveAction = fileMenu->addAction("Save");
    fileMenu->addSeparator();
    QAction *exitAction = fileMenu->addAction("Exit");

    // Connect actions to slots
    connect(newAction, &QAction::triggered, this, &MainWindow::onNew);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpen);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    connect(exitAction, &QAction::triggered, qApp, &QApplication::quit);
}

void MainWindow::onNew()
{
    currentFile.clear();
    textEdit->clear();
}

void MainWindow::onOpen()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        currentFile = fileName;
        QTextStream in(&file);
        QString text = in.readAll();
        textEdit->setText(text);
        file.close();
    }
}

void MainWindow::onSave()
{
    QString fileName;
    if (currentFile.isEmpty())
    {
        fileName = QFileDialog::getSaveFileName(this, "Save");
        currentFile = fileName;
    }
    else
    {
        fileName = currentFile;
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QFile::Text))
    {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    }
}