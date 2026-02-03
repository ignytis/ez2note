#include "mainwindow.hpp"

#include <wx/display.h>
#include <wx/stc/stc.h>
#include <wx/wx.h>

#include "../../../constants.hpp"
#include "../about/aboutwindow.hpp"
#include "../findreplace/findreplacedialog.hpp"
#include "buffers/filebuffer.hpp"
#include "menubar.hpp"

using namespace Ez2note::Gui::Windows::About;
using namespace Ez2note::Gui::Windows::FindReplace;
using namespace Ez2note::Gui::Windows::Main;

/* clang-format off */
wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    // Menu -> File
    EVT_MENU(wxID_NEW, MainWindow::OnNew)
    EVT_MENU(wxID_OPEN, MainWindow::OnOpen)
    EVT_MENU(wxID_SAVE, MainWindow::OnSave)
    EVT_MENU(wxID_SAVEAS, MainWindow::OnSaveAs)
    EVT_MENU(wxID_EXIT, MainWindow::OnExit)
    // Menu -> Edit
    EVT_MENU(ID_MENU_EDIT_FIND_REPLACE, MainWindow::OnFindReplace)
    EVT_MENU(wxID_UNDO, MainWindow::OnUndo)
    EVT_MENU(wxID_REDO, MainWindow::OnRedo)
    // Menu -> View
    EVT_MENU(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS, MainWindow::OnToggleLineNumbers)
    EVT_MENU(ID_MENU_VIEW_TOGGLE_WORD_WRAP, MainWindow::OnToggleWordWrap)
    // Menu -> Help
    EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
    EVT_CLOSE(MainWindow::OnClose)
wxEND_EVENT_TABLE()
    /* clang-format on */

    // a dummy function to make clang-format happy
    void _main_window_dummy(){};

/**
 * Shows a dialog asking the user if they want to save their changes.
 * @return The user's choice (wxID_YES, wxID_NO, or wxID_CANCEL).
 */
int showDocumentModifiedDialog() {
    return wxMessageBox(
        "The document has been modified.\nDo you want to save your "
        "changes?",
        EZ2NOTE_APP_NAME, wxYES_NO | wxCANCEL);
}

MainWindow::MainWindow(Ez2note::Config& config)
    : wxFrame(NULL, wxID_ANY, EZ2NOTE_APP_NAME), config(config) {
#ifdef WIN32
    // Set icons (Windows)
    wxIconBundle icons;
    icons.AddIcon(wxIcon("IDI_APPICON", wxBITMAP_TYPE_ICO_RESOURCE));
    SetIcons(icons);
#endif

    // By default, set the window size to 1/2 of the screen size
    wxDisplay display;
    this->SetSize(display.GetClientArea().GetSize() / 2);

    SetMenuBar(new MenuBar(config));

    screen = new Screen(this, config);

    // Create status bar
    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to %s!", EZ2NOTE_APP_NAME));

    // Open default new file
    screen->OpenNewFile();
}

void MainWindow::OnNew(wxCommandEvent& event) {
    if (screen->IsModified()) {
        switch (showDocumentModifiedDialog()) {
            case wxYES:
                OnSave(event);
                break;
            case wxCANCEL:
                return;
                break;
        }
    }

    screen->OpenNewFile();
}

void MainWindow::OnOpen(wxCommandEvent& event) {
    if (screen->IsModified()) {
        switch (showDocumentModifiedDialog()) {
            case wxYES:
                OnSave(event);
                break;
            case wxCANCEL:
                return;
                break;
        }
    }

    wxFileDialog openFileDialog(this, "Open file", "", "", "All files|*",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    OpenFile(openFileDialog.GetPath());
}

void MainWindow::OpenFile(const wxString& filePath) {
    screen->OpenFile(filePath);
    SetStatusText(wxString::Format("File '%s' opened", filePath));
}

void MainWindow::OnSave(wxCommandEvent& event) {
    Buffers::AbstractBuffer* active = screen->GetActiveBuffer();
    if (!active) return;

    // Check if it's a file buffer
    Buffers::FileBuffer* fileBuffer =
        dynamic_cast<Buffers::FileBuffer*>(active);
    if (!fileBuffer) return;  // Should handle non-file buffers if any

    if (!fileBuffer->HasFile()) {
        OnSaveAs(event);
    } else {
        fileBuffer->SaveFile();
        SetStatusText(wxString::Format("File saved"));
    }
}

void MainWindow::OnSaveAs(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Save file", "", "",
                                "Text files (*.txt)|*.txt",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    Buffers::AbstractBuffer* active = screen->GetActiveBuffer();
    if (active) {
        Buffers::FileBuffer* fileBuffer =
            dynamic_cast<Buffers::FileBuffer*>(active);
        if (fileBuffer) {
            fileBuffer->SaveFileAs(saveFileDialog.GetPath());
            SetStatusText(wxString::Format("File saved to '%s'",
                                           saveFileDialog.GetPath()));
        }
    }
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    AboutWindow* about = new AboutWindow(this);
    about->ShowWindowModal();
}

void MainWindow::OnUndo(wxCommandEvent& event) { screen->Undo(); }

void MainWindow::OnRedo(wxCommandEvent& event) { screen->Redo(); }

void MainWindow::OnFindReplace(wxCommandEvent& event) {
    Buffers::AbstractBuffer* active = screen->GetActiveBuffer();
    if (active && active->GetTextEdit()) {
        FindReplaceDialog* findReplace =
            new FindReplaceDialog(this, active->GetTextEdit());
        findReplace->Show();
    }
}

void MainWindow::OnToggleLineNumbers(wxCommandEvent& event) {
    screen->SetShowLineNumbers(event.IsChecked());
}

void MainWindow::OnToggleWordWrap(wxCommandEvent& event) {
    screen->SetWordWrap(event.IsChecked());
}

void MainWindow::OnExit(wxCommandEvent& event) { Close(true); }

void MainWindow::OnClose(wxCloseEvent& event) {
    if (screen->IsModified()) {
        wxCommandEvent saveEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_SAVE);
        switch (showDocumentModifiedDialog()) {
            case wxYES:
                OnSave(saveEvent);
                break;
            case wxCANCEL:
                return;
                break;
        }
    }

    Destroy();
}
