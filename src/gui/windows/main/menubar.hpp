#ifndef GUI_WINDOWS_MAIN_MENUBAR_HPP
#define GUI_WINDOWS_MAIN_MENUBAR_HPP

#include <wx/wx.h>

#define ID_MENU_VIEW_TOGGLE_LINE_NUMBERS 101
#define ID_MENU_VIEW_TOGGLE_WORD_WRAP 102

namespace Ez2note
{
namespace Gui
{
namespace Windows
{
namespace Main
{

/**
 * Top horizontal menu bar for the main window.
 */
class MenuBar : public wxMenuBar
{
public:
    MenuBar();

};

}
}
}
}

#endif // GUI_WINDOWS_MAIN_MENUBAR_HPP
