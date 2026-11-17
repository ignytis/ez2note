#include "menubar.hpp"

#include <QKeySequence>
#include <QMenu>

using namespace Ez2note::Gui::Windows::Main;

MenuBar::MenuBar(Ez2note::Config& config, QWidget* parent)
    : QMenuBar(parent), config(config) {
    QMenu* menuFile = addMenu("&File");
    actionNew = menuFile->addAction("&New");
    actionNew->setShortcut(QKeySequence::New);
    actionOpen = menuFile->addAction("&Open...");
    actionOpen->setShortcut(QKeySequence::Open);
    actionSave = menuFile->addAction("&Save");
    actionSave->setShortcut(QKeySequence::Save);
    actionSaveAs = menuFile->addAction("Save &As...");
    actionSaveAs->setShortcut(QKeySequence::SaveAs);
    menuFile->addSeparator();
    actionExit = menuFile->addAction("E&xit");
    actionExit->setShortcut(QKeySequence::Quit);

    QMenu* menuEdit = addMenu("&Edit");
    actionUndo = menuEdit->addAction("&Undo");
    actionUndo->setShortcut(QKeySequence::Undo);
    actionRedo = menuEdit->addAction("&Redo");
    actionRedo->setShortcut(QKeySequence::Redo);
    menuEdit->addSeparator();
    actionFindReplace = menuEdit->addAction("Find and Replace...");
    actionFindReplace->setShortcut(QKeySequence("Ctrl+H"));

    QMenu* menuView = addMenu("&View");
    actionToggleLineNumbers = menuView->addAction("Show line numbers");
    actionToggleLineNumbers->setCheckable(true);
    actionToggleLineNumbers->setChecked(
        config.getBool(CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS));
    actionToggleWordWrap = menuView->addAction("Word wrap");
    actionToggleWordWrap->setCheckable(true);
    actionToggleWordWrap->setChecked(
        config.getBool(CONFIG_KEY_EDITOR_WORD_WRAP));

    QMenu* menuHelp = addMenu("&Help");
    actionAbout = menuHelp->addAction("&About");
}
