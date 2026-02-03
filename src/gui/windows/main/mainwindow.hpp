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
    void OpenFile(const wxString& filePath);

   private:
    // Menu -> File
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    // Menu -> Edit
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnFindReplace(wxCommandEvent& event);
    // Menu -> View
    void OnToggleLineNumbers(wxCommandEvent& event);
    void OnToggleWordWrap(wxCommandEvent& event);
    // Menu -> Help
    void OnAbout(wxCommandEvent& event);

    void OnClose(wxCloseEvent& event);

    Screen* screen;
    Ez2note::Config& config;

    wxDECLARE_EVENT_TABLE();
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_MAINWINDOW_HPP
