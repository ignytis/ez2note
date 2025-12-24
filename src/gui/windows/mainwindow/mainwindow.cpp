#include "mainwindow.hpp"
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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
    QAction *saveAsAction = fileMenu->addAction("Save As...");
    fileMenu->addSeparator();
    QAction *exitAction = fileMenu->addAction("Exit");

    // Connect actions to slots
    connect(newAction, &QAction::triggered, this, &MainWindow::onNew);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpen);
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onSaveAs);
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    connect(textEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentWasModified);

    setCurrentFile(QString());
}

void MainWindow::onNew()
{
    if (!maybeSave())
        return;

    textEdit->clear();
    setCurrentFile(QString());
}

void MainWindow::onOpen()
{
    if (!maybeSave())
        return;

    QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
    if (fileName.isEmpty())
        return;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QFile::Text))
        return;

    QTextStream in(&file);
    QString text = in.readAll();
    textEdit->setText(text);
    file.close();
    setCurrentFile(fileName);
}

bool MainWindow::onSave()
{
    if (currentFile.isEmpty()) {
        return onSaveAs();
    }

    QFile file(currentFile);
    if (!file.open(QIODevice::WriteOnly | QFile::Text))
        return false;

    QTextStream out(&file);
    out << textEdit->toPlainText();
    file.close();
    setCurrentFile(currentFile);
    return true;
}

bool MainWindow::onSaveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save");
    if (fileName.isEmpty())
        return false;

    currentFile = fileName;
    return onSave();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    maybeSave() ? event->accept() : event->ignore();
}

void MainWindow::documentWasModified()
{
    setWindowModified(true);
}

bool MainWindow::maybeSave()
{
    if (!textEdit->document()->isModified())
        return true;

    const QMessageBox::StandardButton ret
        = QMessageBox::warning(this, "ez2note",
                               "The document has been modified.\n"
                               "Do you want to save your changes?",
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    switch (ret) {
    case QMessageBox::Save:
        return onSave();
    case QMessageBox::Cancel:
        return false;
    default:
        break;
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;
    textEdit->document()->setModified(false);
    setWindowModified(false);

    QString shownName = currentFile;
    if (currentFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
    setWindowTitle(QString("%1[*] - %2").arg(QFileInfo(shownName).fileName()).arg("ez2note"));
}