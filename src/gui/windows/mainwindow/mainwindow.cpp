#include "mainwindow.hpp"
#include <QFileInfo>
#include <QMessageBox>
#include <QTextStream>
#include "gui/windows/about/about.hpp"

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

    QAction *newAction = fileMenu->addAction("New");
    newAction->setShortcut(QKeySequence::New);
    newAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
    connect(newAction, &QAction::triggered, this, &MainWindow::onNew);

    QAction *openAction = fileMenu->addAction("Open");
    openAction->setShortcut(QKeySequence::Open);
    openAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpen);

    QAction *saveAction = fileMenu->addAction("Save");
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
    connect(saveAction, &QAction::triggered, this, &MainWindow::onSave);

    QAction *saveAsAction = fileMenu->addAction("Save As...");
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSaveAs));
    connect(saveAsAction, &QAction::triggered, this, &MainWindow::onSaveAs);

    fileMenu->addSeparator();

    QAction *exitAction = fileMenu->addAction("Exit");
    exitAction->setShortcut(QKeySequence::Quit);
    exitAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::ApplicationExit));
    connect(exitAction, &QAction::triggered, this, &MainWindow::close);

    // Create a Help menu
    QMenu *helpMenu = menuBar->addMenu("Help");
    QAction *aboutAction = helpMenu->addAction("About");
    aboutAction->setShortcut(QKeySequence::HelpContents);
    aboutAction->setIcon(QIcon::fromTheme(QIcon::ThemeIcon::HelpAbout));
    connect(aboutAction, &QAction::triggered, this, &MainWindow::onAbout);


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
        = QMessageBox::warning(this, APP_NAME,
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
    setWindowTitle(QString("%1[*] - %2").arg(QFileInfo(shownName).fileName()).arg(APP_NAME));
}

void MainWindow::onAbout()
{
    About aboutDialog(this);
    aboutDialog.exec();
}