#include <wx/button.h>
#include <wx/hyperlink.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/wx.h>

#include "aboutwindow.hpp"

#include "../../../constants.hpp"

using namespace Ez2note::Gui::Windows::About;

AboutWindow::AboutWindow(wxWindow *parent)
    : wxDialog(parent, wxID_ANY,
               wxString::Format("About %s", EZ2NOTE_APP_NAME)) {

  wxPanel *panel = new wxPanel(this, wxID_ANY);
  wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

  wxStaticText *appName = new wxStaticText(panel, wxID_ANY, EZ2NOTE_APP_NAME);
  vbox->Add(appName, 0, wxALIGN_CENTER | wxTOP, 10);

  wxStaticText *appDescription =
      new wxStaticText(panel, wxID_ANY, EZ2NOTE_APP_DESCRIPTION);
  vbox->Add(appDescription, 0, wxALIGN_CENTER | wxTOP, 10);

  wxHyperlinkCtrl *homepage = new wxHyperlinkCtrl(
      panel, wxID_ANY, EZ2NOTE_APP_HOMEPAGE, EZ2NOTE_APP_HOMEPAGE);
  vbox->Add(homepage, 0, wxALIGN_CENTER | wxTOP, 10);

  wxHyperlinkCtrl *license = new wxHyperlinkCtrl(
      panel, wxID_ANY, "Licensed under GNU GPL v3",
      "https://github.com/ignytis/ez2note/blob/main/LICENSE");
  vbox->Add(license, 0, wxALIGN_CENTER | wxTOP, 10);

  wxStaticText *libraries =
      new wxStaticText(panel, wxID_ANY, "Libraries used:");
  vbox->Add(libraries, 0, wxALIGN_CENTER | wxTOP, 20);

  wxHyperlinkCtrl *wxWidgetsLicense =
      new wxHyperlinkCtrl(panel, wxID_ANY, wxVERSION_STRING,
                          "https://wxwidgets.org/about/licence/");
  vbox->Add(wxWidgetsLicense, 0, wxALIGN_CENTER | wxTOP, 5);

  wxHyperlinkCtrl *jsonLicense = new wxHyperlinkCtrl(
      panel, wxID_ANY, "nlohmann/json",
      "https://github.com/nlohmann/json/blob/develop/LICENSE.MIT");
  vbox->Add(jsonLicense, 0, wxALIGN_CENTER | wxTOP, 5);

  wxButton *closeButton = new wxButton(panel, wxID_CLOSE);
  vbox->Add(closeButton, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

  panel->SetSizer(vbox);

  wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
  mainSizer->Add(panel, 1, wxEXPAND | wxALL, 10);
  SetSizerAndFit(mainSizer);

  Connect(wxID_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED,
          wxCommandEventHandler(AboutWindow::OnClose));

  Centre();
}

void AboutWindow::OnClose(wxCommandEvent &WXUNUSED(event)) { Close(); }
