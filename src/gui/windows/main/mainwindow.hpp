#ifndef GUI_WINDOWS_MAIN_MAINWINDOW_HPP
#define GUI_WINDOWS_MAIN_MAINWINDOW_HPP

#include <wx/wx.h>

#include "../../../config.hpp"
#include "buffers/richfilebuffer.hpp"
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
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

    void OnClose(wxCloseEvent& event);
    void OnBufferChanged(wxCommandEvent& event);

    Screen* screen;
    Ez2note::Config& config;

    // Track currently bound buffer to unbind events later
    Ez2note::Gui::Windows::Main::Buffers::RichFileBuffer* currentBoundBuffer;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_MAINWINDOW_HPP
