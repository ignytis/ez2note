#include "mainwindow.hpp"

#include <wx/display.h>
#include <wx/stc/stc.h>
#include <wx/wx.h>

#include "../../../constants.hpp"
#include "../about/aboutwindow.hpp"
#include "buffers/richfilebuffer.hpp"
#include "menubar.hpp"  // For constants

using namespace Ez2note::Gui::Windows::Main;

// TODO: move the file specific logic to AbstractFileBuffer or derived classes

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

    screen = new Screen(this, config);
    currentBoundBuffer = nullptr;

    // Bind global events
    Bind(wxEVT_MENU, &MainWindow::OnNew, this, wxID_NEW);
    Bind(wxEVT_MENU, &MainWindow::OnOpen, this, wxID_OPEN);
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this);

    // Bind buffer change event from Screen
    screen->Bind(DATA_BUFFER_CHANGED, &MainWindow::OnBufferChanged, this);

    // Create status bar
    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to %s!", EZ2NOTE_APP_NAME));

    // Open default new file
    screen->OpenNewFile();
}

void MainWindow::OnNew(wxCommandEvent& event) {
    if (screen->IsModified()) {
        switch (showDocumentModifiedDialog()) {
            case wxYES: {
                wxCommandEvent saveEvent(wxEVT_COMMAND_MENU_SELECTED,
                                         wxID_SAVE);
                screen->GetActiveBuffer()->GetEventHandler()->ProcessEvent(
                    saveEvent);
                break;
            }
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
            case wxYES: {
                wxCommandEvent saveEvent(wxEVT_COMMAND_MENU_SELECTED,
                                         wxID_SAVE);
                screen->GetActiveBuffer()->GetEventHandler()->ProcessEvent(
                    saveEvent);
                break;
            }
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

void MainWindow::OnBufferChanged(wxCommandEvent& event) {
    Buffers::AbstractBuffer* active = screen->GetActiveBuffer();
    if (!active) return;

    AbstractMenu* menu = active->GetMenu();
    SetMenuBar(menu);

    // TODO: binding and unbinding should be moved to AbstractBuffer or chilren classes

    // Unbind previous buffer events
    if (currentBoundBuffer) {
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnSave, currentBoundBuffer,
               wxID_SAVE);
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnSaveAs,
               currentBoundBuffer, wxID_SAVEAS);
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnUndo, currentBoundBuffer,
               wxID_UNDO);
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnRedo, currentBoundBuffer,
               wxID_REDO);
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnFindReplace,
               currentBoundBuffer, 100);  // 100 is ID_MENU_EDIT_FIND_REPLACE from findreplacedialog
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnToggleLineNumbers,
               currentBoundBuffer, ID_MENU_VIEW_TOGGLE_LINE_NUMBERS);
        Unbind(wxEVT_MENU, &Buffers::RichFileBuffer::OnToggleWordWrap,
               currentBoundBuffer, ID_MENU_VIEW_TOGGLE_WORD_WRAP);
        currentBoundBuffer = nullptr;
    }

    Buffers::RichFileBuffer* richBuffer =
        dynamic_cast<Buffers::RichFileBuffer*>(active);
    if (richBuffer) {
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnSave, richBuffer,
             wxID_SAVE);
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnSaveAs, richBuffer,
             wxID_SAVEAS);
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnUndo, richBuffer,
             wxID_UNDO);
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnRedo, richBuffer,
             wxID_REDO);
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnFindReplace, richBuffer,
             100);  // 100 is ID_MENU_EDIT_FIND_REPLACE from findreplacedialog
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnToggleLineNumbers,
             richBuffer, ID_MENU_VIEW_TOGGLE_LINE_NUMBERS);
        Bind(wxEVT_MENU, &Buffers::RichFileBuffer::OnToggleWordWrap, richBuffer,
             ID_MENU_VIEW_TOGGLE_WORD_WRAP);

        currentBoundBuffer = richBuffer;
    }
}

void MainWindow::OnClose(wxCloseEvent& event) {
    if (screen->IsModified()) {
        wxCommandEvent saveEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_SAVE);
        switch (showDocumentModifiedDialog()) {
            case wxYES: {
                screen->GetActiveBuffer()->GetEventHandler()->ProcessEvent(
                    saveEvent);
                break;
            }
            case wxCANCEL:
                return;
                break;
        }
    }

    Destroy();
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    Ez2note::Gui::Windows::About::AboutWindow* about =
        new Ez2note::Gui::Windows::About::AboutWindow(this);
    about->ShowWindowModal();
}

void MainWindow::OnExit(wxCommandEvent& event) { Close(true); }
