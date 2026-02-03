#include "abstractbuffer.hpp"

using namespace Ez2note::Gui::Windows::Main::Buffers;

AbstractBuffer::AbstractBuffer(wxWindow* parent, Ez2note::Config& config)
    : wxPanel(parent, wxID_ANY), config(config) {
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
}

void AbstractBuffer::Undo() { textEdit->Undo(); }

void AbstractBuffer::Redo() { textEdit->Redo(); }

void AbstractBuffer::SetShowLineNumbers(bool show) {
    textEdit->SetMarginWidth(1, show ? 50 : 0);
}

void AbstractBuffer::SetWordWrap(bool wrap) {
    textEdit->SetWrapMode(wrap ? wxSTC_WRAP_WORD : wxSTC_WRAP_NONE);
}

bool AbstractBuffer::IsModified() const { return textEdit->IsModified(); }
