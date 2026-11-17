#ifndef GUI_WINDOWS_ABOUT_ABOUTWINDOW_HPP
#define GUI_WINDOWS_ABOUT_ABOUTWINDOW_HPP

#include <QDialog>

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace About {

/** "About" dialog with version, license and used libraries. */
class AboutWindow : public QDialog {
    Q_OBJECT

   public:
    explicit AboutWindow(QWidget* parent);
};

}  // namespace About
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_ABOUT_ABOUTWINDOW_HPP
