#ifndef GUI_WINDOWS_MAIN_MENUBAR_HPP
#define GUI_WINDOWS_MAIN_MENUBAR_HPP

#include <QAction>
#include <QMenuBar>

#include "../../../config.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {

/**
 * Top horizontal menu bar for the main window. Actions are public so that
 * the main window can connect them to its slots.
 */
class MenuBar : public QMenuBar {
    Q_OBJECT

   public:
    MenuBar(Ez2note::Config& config, QWidget* parent = nullptr);

    QAction* actionNew;
    QAction* actionOpen;
    QAction* actionSave;
    QAction* actionSaveAs;
    QAction* actionExit;
    QAction* actionUndo;
    QAction* actionRedo;
    QAction* actionFindReplace;
    QAction* actionToggleLineNumbers;
    QAction* actionToggleWordWrap;
    QAction* actionAbout;

   private:
    Ez2note::Config& config;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_MENUBAR_HPP
