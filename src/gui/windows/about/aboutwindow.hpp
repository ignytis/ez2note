#ifndef GUI_WINDOWS_ABOUT_ABOUTWINDOW_HPP
#define GUI_WINDOWS_ABOUT_ABOUTWINDOW_HPP

#include <wx/wx.h>

namespace Ez2note
{
namespace Gui
{
namespace Windows
{
namespace About
{

class AboutWindow : public wxDialog
{
public:
    AboutWindow(wxWindow *parent);
    void OnClose(wxCommandEvent& event);
};

}
}
}
}


#endif // GUI_WINDOWS_ABOUT_ABOUT_HPP
