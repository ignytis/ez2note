#ifndef GUI_WINDOWS_ABSTRACTMENU_HPP
#define GUI_WINDOWS_ABSTRACTMENU_HPP

#include <wx/wx.h>

namespace Ez2note {
namespace Gui {
namespace Windows {

class AbstractMenu : public wxMenuBar {
   public:
    AbstractMenu() = default;
    virtual ~AbstractMenu() = default;
};

}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_ABSTRACTMENU_HPP
