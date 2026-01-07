#ifndef GUI_WINDOWS_MAIN_MAINWINDOW_HPP
#define GUI_WINDOWS_MAIN_MAINWINDOW_HPP

#include <wx/stc/stc.h>
#include <wx/wx.h>

#include "../../../config.hpp"

namespace Ez2note
{
namespace Gui
{
namespace Windows
{
namespace Main
{

class MainWindow : public wxFrame
{
public:
    MainWindow(Ez2note::Config &config);
    void OpenFile(const wxString &filePath);

private:
    void OnNew(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnSaveAs(wxCommandEvent &event);
    void OnAbout(wxCommandEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnFindReplace(wxCommandEvent &event);
    void OnToggleLineNumbers(wxCommandEvent &event);
    void OnToggleWordWrap(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);

    void doSaveFile();                  // saves the current file
    void doSaveFile(wxString filePath); // saves the specified file and sets it as current

    // TODO: make it even more simple by default. But this widget might be useful in advanced mode
    wxStyledTextCtrl *textEdit;
    wxString currentFile;
    Ez2note::Config &config;

    wxDECLARE_EVENT_TABLE();
};

} // namespace Main
} // namespace Windows
} // namespace Gui
} // namespace Ez2note

#endif // GUI_WINDOWS_MAIN_MAINWINDOW_HPP
