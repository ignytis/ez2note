#include "richfilebuffer.hpp"

using namespace Ez2note::Gui::Windows::Main::Buffers;

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
