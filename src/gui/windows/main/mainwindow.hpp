#ifndef GUI_WINDOWS_MAIN_MAINWINDOW_HPP
#define GUI_WINDOWS_MAIN_MAINWINDOW_HPP

#include <QCloseEvent>
#include <QMainWindow>
#include <QString>

#include "../../../config.hpp"
#include "screen.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {

/** The main application window. */
class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(Ez2note::Config& config);
    void OpenFile(const QString& filePath);

   protected:
    void closeEvent(QCloseEvent* event) override;

   private slots:
    // Menu -> File
    void OnNew();
    void OnOpen();
    bool OnSave();
    bool OnSaveAs();
    // Menu -> Edit
    void OnFindReplace();
    // Menu -> Help
    void OnAbout();

   private:
    /**
     * Asks to save unsaved changes.
     * @return false if the user cancelled the operation.
     */
    bool ConfirmDiscardChanges();

    Screen* screen;
    Ez2note::Config& config;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_MAINWINDOW_HPP
