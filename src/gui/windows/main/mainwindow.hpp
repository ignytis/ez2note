#ifndef GUI_WINDOWS_MAIN_MAINWINDOW_HPP
#define GUI_WINDOWS_MAIN_MAINWINDOW_HPP

#include <wx/wx.h>

#include "../../../config.hpp"
#include "screen.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {

class MainWindow : public wxFrame {
   public:
    MainWindow(Ez2note::Config& config);
    Screen* GetScreen() const { return screen; }

   private:
    // Menu -> File
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnClose(wxCloseEvent& event);
    void OnBufferChanged(wxCommandEvent& event);

    Screen* screen;
    Ez2note::Config& config;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_MAINWINDOW_HPP
