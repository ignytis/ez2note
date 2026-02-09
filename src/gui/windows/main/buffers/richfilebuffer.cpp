#include "richfilebuffer.hpp"

#include <wx/msgdlg.h>

#include "../../../../constants.hpp"
#include "../../findreplace/findreplacedialog.hpp"

using namespace Ez2note::Gui::Windows::Main::Buffers;
using Ez2note::Gui::Windows::AbstractMenu;

namespace {
int showDocumentModifiedDialog() {
    return wxMessageBox(
        "The document has been modified.\nDo you want to save your "
        "changes?",
        EZ2NOTE_APP_NAME, wxYES_NO | wxCANCEL);
}
}  // namespace

RichFileBuffer::RichFileBuffer(wxWindow* parent, wxFrame* mainFrame,
                               Ez2note::Config& config,
                               const wxString& filePath)
    : AbstractFileBuffer(parent, mainFrame, config, filePath) {
    textEdit = new wxStyledTextCtrl(this, wxID_ANY);

    // Initial setup from config
    textEdit->SetMarginWidth(
        1, config.getBool(CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS) ? 50 : 0);
    textEdit->SetMarginType(1, wxSTC_MARGIN_NUMBER);
    textEdit->SetWrapMode(config.getBool(CONFIG_KEY_EDITOR_WORD_WRAP)
                              ? wxSTC_WRAP_WORD
                              : wxSTC_WRAP_NONE);

    // Layout
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(textEdit, 1, wxEXPAND);
    SetSizer(sizer);

    if (!filePath.IsEmpty()) {
        LoadFile(filePath);
    }

    menuBar = new MenuBar(config);

    Bind(wxEVT_SHOW, &RichFileBuffer::OnShow, this);
}

void RichFileBuffer::Undo() { textEdit->Undo(); }

void RichFileBuffer::Redo() { textEdit->Redo(); }

void RichFileBuffer::SetShowLineNumbers(bool show) {
    textEdit->SetMarginWidth(1, show ? 50 : 0);
}

void RichFileBuffer::SetWordWrap(bool wrap) {
    textEdit->SetWrapMode(wrap ? wxSTC_WRAP_WORD : wxSTC_WRAP_NONE);
}

bool RichFileBuffer::IsModified() const { return textEdit->IsModified(); }

bool RichFileBuffer::LoadFile(const wxString& path) {
    if (textEdit->LoadFile(path)) {
        filePath = path;
        return true;
    }
    return false;
}

bool RichFileBuffer::SaveFile() {
    if (filePath.IsEmpty()) {
        return false;
    }
    return textEdit->SaveFile(filePath);
}

bool RichFileBuffer::SaveFileAs(const wxString& path) {
    if (textEdit->SaveFile(path)) {
        filePath = path;
        return true;
    }
    return false;
}

void RichFileBuffer::OnShow(wxShowEvent& event) {
    if (event.GetEventObject() != this) return;

    if (event.IsShown()) {
        // Bind menu events
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnNew, this,
                              wxID_NEW);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnOpen, this,
                              wxID_OPEN);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnSave, this,
                              wxID_SAVE);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnSaveAs, this,
                              wxID_SAVEAS);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnUndo, this,
                              wxID_UNDO);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnRedo, this,
                              wxID_REDO);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnFindReplace, this,
                              100);  // 100 is ID_MENU_EDIT_FIND_REPLACE
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnToggleLineNumbers,
                              this, ID_MENU_VIEW_TOGGLE_LINE_NUMBERS);
        this->mainFrame->Bind(wxEVT_MENU, &RichFileBuffer::OnToggleWordWrap,
                              this, ID_MENU_VIEW_TOGGLE_WORD_WRAP);
    } else {
        // Unbind menu events
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnNew, this,
                                wxID_NEW);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnOpen, this,
                                wxID_OPEN);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnSave, this,
                                wxID_SAVE);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnSaveAs, this,
                                wxID_SAVEAS);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnUndo, this,
                                wxID_UNDO);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnRedo, this,
                                wxID_REDO);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnFindReplace,
                                this, 100);
        this->mainFrame->Unbind(wxEVT_MENU,
                                &RichFileBuffer::OnToggleLineNumbers, this,
                                ID_MENU_VIEW_TOGGLE_LINE_NUMBERS);
        this->mainFrame->Unbind(wxEVT_MENU, &RichFileBuffer::OnToggleWordWrap,
                                this, ID_MENU_VIEW_TOGGLE_WORD_WRAP);
    }

    event.Skip();
}

void RichFileBuffer::OnNew(wxCommandEvent& event) {
    if (IsModified()) {
        switch (showDocumentModifiedDialog()) {
            case wxYES: {
                if (HasFile()) {
                    SaveFile();
                } else {
                    OnSaveAs(event);
                }
                break;
            }
            case wxCANCEL:
                return;
        }
    }

    textEdit->ClearAll();
    textEdit->SetModified(false);
    filePath = "";
}

void RichFileBuffer::OnOpen(wxCommandEvent& event) {
    if (IsModified()) {
        switch (showDocumentModifiedDialog()) {
            case wxYES: {
                if (HasFile()) {
                    SaveFile();
                } else {
                    OnSaveAs(event);
                }
                break;
            }
            case wxCANCEL:
                return;
        }
    }

    wxFileDialog openFileDialog(this, "Open file", "", "", "All files|*",
                                wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL) return;

    filePath = openFileDialog.GetPath();
    textEdit->LoadFile(filePath);
}

void RichFileBuffer::OnSave(wxCommandEvent& event) {
    if (HasFile()) {
        SaveFile();
    } else {
        OnSaveAs(event);
    }
}

void RichFileBuffer::OnSaveAs(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Save file", "", "",
                                "Text files (*.txt)|*.txt",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    SaveFileAs(saveFileDialog.GetPath());
}

void RichFileBuffer::OnUndo(wxCommandEvent& event) { Undo(); }

void RichFileBuffer::OnRedo(wxCommandEvent& event) { Redo(); }

void RichFileBuffer::OnFindReplace(wxCommandEvent& event) {
    if (GetTextEdit()) {
        Ez2note::Gui::Windows::FindReplace::FindReplaceDialog* findReplace =
            new Ez2note::Gui::Windows::FindReplace::FindReplaceDialog(
                this, GetTextEdit());
        findReplace->Show();
    }
}

void RichFileBuffer::OnToggleLineNumbers(wxCommandEvent& event) {
    SetShowLineNumbers(event.IsChecked());
}

void RichFileBuffer::OnToggleWordWrap(wxCommandEvent& event) {
    SetWordWrap(event.IsChecked());
}

AbstractMenu* RichFileBuffer::GetMenu() { return menuBar; }

RichFileBuffer::MenuBar::MenuBar(Ez2note::Config& config) {
    wxMenu* menuFile = new wxMenu;
    menuFile->Append(wxID_NEW);
    menuFile->Append(wxID_OPEN);
    menuFile->Append(wxID_SAVE);
    menuFile->Append(wxID_SAVEAS);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuEdit = new wxMenu;
    menuEdit->Append(wxID_UNDO);
    menuEdit->Append(wxID_REDO);
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_MENU_EDIT_FIND_REPLACE, "Find and Replace...\tCtrl+H");

    wxMenu* menuView = new wxMenu;
    menuView->AppendCheckItem(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS,
                              "Show line numbers");
    menuView->Check(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS,
                    config.getBool(CONFIG_KEY_EDITOR_SHOW_LINE_NUMBERS));
    menuView->AppendCheckItem(ID_MENU_VIEW_TOGGLE_WORD_WRAP, "Word wrap");
    menuView->Check(ID_MENU_VIEW_TOGGLE_WORD_WRAP,
                    config.getBool(CONFIG_KEY_EDITOR_WORD_WRAP));

    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    Append(menuFile, "&File");
    Append(menuEdit, "&Edit");
    Append(menuView, "&View");
    Append(menuHelp, "&Help");
}
