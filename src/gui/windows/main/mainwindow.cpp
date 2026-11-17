#include "mainwindow.hpp"

#include <QFileDialog>
#include <QGuiApplication>
#include <QMessageBox>
#include <QScreen>
#include <QStatusBar>

#include "../../../constants.hpp"
#include "../about/aboutwindow.hpp"
#include "../findreplace/findreplacedialog.hpp"
#include "buffers/filebuffer.hpp"
#include "menubar.hpp"

using namespace Ez2note::Gui::Windows::About;
using namespace Ez2note::Gui::Windows::FindReplace;
using namespace Ez2note::Gui::Windows::Main;

MainWindow::MainWindow(Ez2note::Config& config) : config(config) {
    setWindowTitle(EZ2NOTE_APP_NAME);

    // By default, set the window size to 1/2 of the screen size
    resize(QGuiApplication::primaryScreen()->availableGeometry().size() / 2);

    MenuBar* menuBar = new MenuBar(config, this);
    setMenuBar(menuBar);

    screen = new Screen(this, config);
    setCentralWidget(screen);

    statusBar()->showMessage(QString("Welcome to %1!").arg(EZ2NOTE_APP_NAME));

    // Menu -> File
    connect(menuBar->actionNew, &QAction::triggered, this, &MainWindow::OnNew);
    connect(menuBar->actionOpen, &QAction::triggered, this,
            &MainWindow::OnOpen);
    connect(menuBar->actionSave, &QAction::triggered, this,
            &MainWindow::OnSave);
    connect(menuBar->actionSaveAs, &QAction::triggered, this,
            &MainWindow::OnSaveAs);
    connect(menuBar->actionExit, &QAction::triggered, this, &QWidget::close);
    // Menu -> Edit
    connect(menuBar->actionUndo, &QAction::triggered, screen, &Screen::Undo);
    connect(menuBar->actionRedo, &QAction::triggered, screen, &Screen::Redo);
    connect(menuBar->actionFindReplace, &QAction::triggered, this,
            &MainWindow::OnFindReplace);
    // Menu -> View
    connect(menuBar->actionToggleLineNumbers, &QAction::toggled, screen,
            &Screen::SetShowLineNumbers);
    connect(menuBar->actionToggleWordWrap, &QAction::toggled, screen,
            &Screen::SetWordWrap);
    // Menu -> Help
    connect(menuBar->actionAbout, &QAction::triggered, this,
            &MainWindow::OnAbout);

    // Open default new file
    screen->OpenNewFile();
}

bool MainWindow::ConfirmDiscardChanges() {
    if (!screen->IsModified()) return true;

    QMessageBox::StandardButton choice = QMessageBox::question(
        this, EZ2NOTE_APP_NAME,
        "The document has been modified.\nDo you want to save your changes?",
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    if (choice == QMessageBox::Cancel) return false;
    return choice == QMessageBox::Save ? OnSave() : true;
}

void MainWindow::OnNew() {
    if (!ConfirmDiscardChanges()) return;
    screen->OpenNewFile();
}

void MainWindow::OnOpen() {
    if (!ConfirmDiscardChanges()) return;

    QString path =
        QFileDialog::getOpenFileName(this, "Open file", "", "All files (*)");
    if (path.isEmpty()) return;

    OpenFile(path);
}

void MainWindow::OpenFile(const QString& filePath) {
    screen->OpenFile(filePath);
    statusBar()->showMessage(QString("File '%1' opened").arg(filePath));
}

bool MainWindow::OnSave() {
    Buffers::FileBuffer* fileBuffer =
        qobject_cast<Buffers::FileBuffer*>(screen->GetActiveBuffer());
    if (!fileBuffer) return false;
    if (!fileBuffer->HasFile()) return OnSaveAs();

    bool ok = fileBuffer->SaveFile();
    statusBar()->showMessage(ok ? "File saved" : "Failed to save the file");
    return ok;
}

bool MainWindow::OnSaveAs() {
    Buffers::FileBuffer* fileBuffer =
        qobject_cast<Buffers::FileBuffer*>(screen->GetActiveBuffer());
    if (!fileBuffer) return false;

    QString path = QFileDialog::getSaveFileName(this, "Save file", "",
                                                "Text files (*.txt)");
    if (path.isEmpty()) return false;

    bool ok = fileBuffer->SaveFileAs(path);
    statusBar()->showMessage(ok ? QString("File saved to '%1'").arg(path)
                                : "Failed to save the file");
    return ok;
}

void MainWindow::OnAbout() {
    AboutWindow* about = new AboutWindow(this);
    about->setAttribute(Qt::WA_DeleteOnClose);
    about->open();
}

void MainWindow::OnFindReplace() {
    Buffers::AbstractBuffer* active = screen->GetActiveBuffer();
    if (!active || !active->GetTextEdit()) return;

    FindReplaceDialog* findReplace =
        new FindReplaceDialog(this, active->GetTextEdit());
    findReplace->setAttribute(Qt::WA_DeleteOnClose);
    findReplace->show();
}

void MainWindow::closeEvent(QCloseEvent* event) {
    ConfirmDiscardChanges() ? event->accept() : event->ignore();
}
