#include <wx/wx.h>
#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/sizer.h>
#include <wx/stattext.h>

#include "aboutwindow.hpp"

#include "../../../constants.hpp"

using namespace Ez2note::Gui::Windows::About;

AboutWindow::AboutWindow(wxWindow *parent)
    : wxDialog(parent, wxID_ANY, "About ez2note")
{
    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    wxStaticText *appName = new wxStaticText(panel, wxID_ANY, EZ2NOTE_APP_NAME);
    vbox->Add(appName, 0, wxALIGN_CENTER | wxTOP, 10);

    wxStaticText *appDescription = new wxStaticText(panel, wxID_ANY, EZ2NOTE_APP_DESCRIPTION);
    vbox->Add(appDescription, 0, wxALIGN_CENTER | wxTOP, 10);

    wxHyperlinkCtrl *homepage = new wxHyperlinkCtrl(panel, wxID_ANY, EZ2NOTE_APP_HOMEPAGE, EZ2NOTE_APP_HOMEPAGE);
    vbox->Add(homepage, 0, wxALIGN_CENTER | wxTOP, 10);

    wxStaticText *wxVersion = new wxStaticText(panel, wxID_ANY, wxVERSION_STRING);
    vbox->Add(wxVersion, 0, wxALIGN_CENTER | wxTOP, 10);

    wxStaticText *license = new wxStaticText(panel, wxID_ANY, "Licensed under GNU GPL v3");
    vbox->Add(license, 0, wxALIGN_CENTER | wxTOP, 10);

    wxButton *closeButton = new wxButton(panel, wxID_CLOSE);
    vbox->Add(closeButton, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

    panel->SetSizer(vbox);

    Connect(wxID_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(AboutWindow::OnClose));

    Centre();
}

void AboutWindow::OnClose(wxCommandEvent& WXUNUSED(event))
{
    Close();
}
