#include "richfilebuffer.hpp"

#include "../../findreplace/findreplacedialog.hpp"
#include "../menubar.hpp"  // For IDs like ID_MENU_EDIT_FIND_REPLACE

using namespace Ez2note::Gui::Windows::Main::Buffers;
using Ez2note::Gui::Windows::AbstractMenu;

RichFileBuffer::RichFileBuffer(wxWindow* parent, Ez2note::Config& config,
                               const wxString& filePath)
    : AbstractFileBuffer(parent, config, filePath) {
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

void RichFileBuffer::OnSave(wxCommandEvent& event) {
    if (!HasFile()) {
        OnSaveAs(event);
    } else {
        SaveFile();
        // SetStatusText(wxString::Format("File saved")); // No access to
        // StatusBar here easily
    }
}

void RichFileBuffer::OnSaveAs(wxCommandEvent& event) {
    wxFileDialog saveFileDialog(this, "Save file", "", "",
                                "Text files (*.txt)|*.txt",
                                wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL) return;

    SaveFileAs(saveFileDialog.GetPath());
    // SetStatusText ...
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
