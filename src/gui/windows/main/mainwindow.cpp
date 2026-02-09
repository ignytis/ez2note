#include "mainwindow.hpp"

#include <wx/display.h>
#include <wx/stc/stc.h>
#include <wx/wx.h>

#include "../../../constants.hpp"
#include "../about/aboutwindow.hpp"

using namespace Ez2note::Gui::Windows::Main;

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

    // Bind global events
    Bind(wxEVT_MENU, &MainWindow::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainWindow::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_CLOSE_WINDOW, &MainWindow::OnClose, this);

    // Bind buffer change event from Screen
    Bind(DATA_BUFFER_CHANGED, &MainWindow::OnBufferChanged, this);

    // Create status bar
    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to %s!", EZ2NOTE_APP_NAME));
}

void MainWindow::OnBufferChanged(wxCommandEvent& event) {
    Buffers::AbstractBuffer* active = screen->GetActiveBuffer();
    if (!active) return;

    AbstractMenu* menu = active->GetMenu();
    SetMenuBar(menu);
}

void MainWindow::OnClose(wxCloseEvent& event) {
    // TODO: go over screens and buffers and ask if any action needed

    Destroy();
}

void MainWindow::OnAbout(wxCommandEvent& event) {
    Ez2note::Gui::Windows::About::AboutWindow* about =
        new Ez2note::Gui::Windows::About::AboutWindow(this);
    about->ShowWindowModal();
}

void MainWindow::OnExit(wxCommandEvent& event) { Close(true); }
