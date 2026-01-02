#include "findreplacedialog.hpp"

using namespace Ez2note::Gui::Windows::FindReplace;

enum {
    ID_FIND_TEXT = 1,
    ID_REPLACE_TEXT,
    ID_FINDNEXT_BUTTON,
    ID_FINDPREV_BUTTON,
    ID_REPLACE_BUTTON,
    ID_REPLACE_ALL_BUTTON
};

wxBEGIN_EVENT_TABLE(FindReplaceDialog, wxDialog)
    EVT_BUTTON(ID_FINDNEXT_BUTTON, FindReplaceDialog::OnFindNext)
    EVT_BUTTON(ID_FINDPREV_BUTTON, FindReplaceDialog::OnFindPrev)
    EVT_BUTTON(ID_REPLACE_BUTTON, FindReplaceDialog::OnReplace)
    EVT_BUTTON(ID_REPLACE_ALL_BUTTON, FindReplaceDialog::OnReplaceAll)
wxEND_EVENT_TABLE()

FindReplaceDialog::FindReplaceDialog(wxWindow *parent, wxStyledTextCtrl *textEdit)
    : wxDialog(parent, wxID_ANY, "Find and Replace"), textEdit(textEdit) {

    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer *gridSizer = new wxFlexGridSizer(2, 2, 5, 5);
    gridSizer->AddGrowableCol(1);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Find:"), 0, wxALIGN_CENTER_VERTICAL);
    findText = new wxTextCtrl(this, ID_FIND_TEXT);
    gridSizer->Add(findText, 1, wxEXPAND);

    gridSizer->Add(new wxStaticText(this, wxID_ANY, "Replace with:"), 0, wxALIGN_CENTER_VERTICAL);
    replaceText = new wxTextCtrl(this, ID_REPLACE_TEXT);
    gridSizer->Add(replaceText, 1, wxEXPAND);

    sizer->Add(gridSizer, 1, wxEXPAND | wxALL, 10);

    wxBoxSizer *buttonSizer = new wxBoxSizer(wxHORIZONTAL);
    buttonSizer->Add(new wxButton(this, ID_FINDNEXT_BUTTON, "Find next"), 0, wxRIGHT, 5);
    buttonSizer->Add(new wxButton(this, ID_FINDPREV_BUTTON, "Find previous"), 0, wxRIGHT, 5);
    buttonSizer->Add(new wxButton(this, ID_REPLACE_BUTTON, "Replace"), 0, wxRIGHT, 5);
    buttonSizer->Add(new wxButton(this, ID_REPLACE_ALL_BUTTON, "Replace All"), 0, wxRIGHT, 5);
    buttonSizer->Add(new wxButton(this, wxID_CANCEL, "Cancel"), 0);

    sizer->Add(buttonSizer, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    SetSizerAndFit(sizer);

    Connect(wxID_CLOSE, wxEVT_COMMAND_BUTTON_CLICKED,
            wxCommandEventHandler(FindReplaceDialog::OnCancel));

}

void FindReplaceDialog::OnFindNext(wxCommandEvent &event) {
    wxString searchTerm = findText->GetValue();
    if (searchTerm.IsEmpty()) {
        return;
    }

    textEdit->SearchAnchor();
    // FIXME: it search the first occurrence only. Need to save the state of search and look up further occurrences
    int nextPos = textEdit->SearchNext(0, searchTerm);

    if (nextPos != wxSTC_INVALID_POSITION) {
        textEdit->SetSelection(nextPos, nextPos + searchTerm.Length());
        textEdit->EnsureCaretVisible();
    } else {
        wxMessageBox("Text not found.", "Find", wxOK | wxICON_INFORMATION);
    }
}

void FindReplaceDialog::OnFindPrev(wxCommandEvent &event) {
    wxString searchTerm = findText->GetValue();
    if (searchTerm.IsEmpty()) {
        return;
    }

    textEdit->SearchAnchor();
    // FIXME: it search the first occurrence only. Need to save the state of search and look up further occurrences
    int prevPos = textEdit->SearchPrev(0, searchTerm);

    if (prevPos != wxSTC_INVALID_POSITION) {
        textEdit->SetSelection(prevPos, prevPos + searchTerm.Length());
        textEdit->EnsureCaretVisible();
    } else {
        wxMessageBox("Text not found.", "Find", wxOK | wxICON_INFORMATION);
    }
}

void FindReplaceDialog::OnReplace(wxCommandEvent &event) {
    wxString searchTerm = findText->GetValue();
    wxString replaceTerm = replaceText->GetValue();

    if (searchTerm.IsEmpty()) {
        return;
    }

    if (textEdit->GetSelectedText() == searchTerm) {
        textEdit->ReplaceSelection(replaceTerm);
    }

    OnFindNext(event);
}

void FindReplaceDialog::OnReplaceAll(wxCommandEvent &event) {
    wxString searchTerm = findText->GetValue();
    wxString replaceTerm = replaceText->GetValue();

    if (searchTerm.IsEmpty()) {
        return;
    }

    int count = 0;
    textEdit->GotoPos(0);
    textEdit->SearchAnchor();

    while (textEdit->SearchNext(0, searchTerm) != wxSTC_INVALID_POSITION) {
        textEdit->ReplaceSelection(replaceTerm);
        count++;
    }

    wxMessageBox(wxString::Format("Replaced %d occurrences.", count), "Replace All", wxOK | wxICON_INFORMATION);
}

void FindReplaceDialog::OnCancel(wxCommandEvent &event) {
    Close();
}
