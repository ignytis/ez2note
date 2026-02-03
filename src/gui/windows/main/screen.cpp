#include "screen.hpp"

#include "buffers/filebuffer.hpp"

using namespace Ez2note::Gui::Windows::Main;

Screen::Screen(wxWindow* parent, Ez2note::Config& config)
    : wxPanel(parent, wxID_ANY), activeBuffer(nullptr), config(config) {
    sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);
}

Screen::~Screen() {
    // Buffers are children of this window, so they are deleted automatically by
    // wxWidgets. We just need to clear the vector to avoid dangling pointers if
    // we accessed them in destructor later (though we don't).
    buffers.clear();
}

Buffers::AbstractBuffer* Screen::OpenNewFile() {
    Buffers::FileBuffer* newBuffer = new Buffers::FileBuffer(this, config);
    buffers.push_back(newBuffer);
    SetActiveBuffer(newBuffer);
    return newBuffer;
}

Buffers::AbstractBuffer* Screen::OpenFile(const wxString& filePath) {
    Buffers::FileBuffer* newBuffer =
        new Buffers::FileBuffer(this, config, filePath);
    buffers.push_back(newBuffer);
    SetActiveBuffer(newBuffer);
    return newBuffer;
}

void Screen::CloseBuffer(Buffers::AbstractBuffer* buffer) {
    // Find and remove from vector
    for (auto it = buffers.begin(); it != buffers.end(); ++it) {
        if (*it == buffer) {
            buffers.erase(it);
            break;
        }
    }

    // If it was active, switch to another
    if (activeBuffer == buffer) {
        if (!buffers.empty()) {
            SetActiveBuffer(buffers.back());
        } else {
            activeBuffer = nullptr;
        }
    }

    // Destroy the window
    buffer->Destroy();
    UpdateLayout();
}

Buffers::AbstractBuffer* Screen::GetActiveBuffer() const {
    return activeBuffer;
}

void Screen::SetActiveBuffer(Buffers::AbstractBuffer* buffer) {
    activeBuffer = buffer;
    UpdateLayout();
}

void Screen::UpdateLayout() {
    // Hide all buffers
    for (auto buf : buffers) {
        buf->Show(false);
    }

    sizer->Clear(false);  // remove items from sizer but don't destroy windows

    if (activeBuffer) {
        activeBuffer->Show(true);
        sizer->Add(activeBuffer, 1, wxEXPAND);
    }

    Layout();
    Refresh();
}

void Screen::Undo() {
    if (activeBuffer) activeBuffer->Undo();
}

void Screen::Redo() {
    if (activeBuffer) activeBuffer->Redo();
}

void Screen::SetShowLineNumbers(bool show) {
    if (activeBuffer) activeBuffer->SetShowLineNumbers(show);
}

void Screen::SetWordWrap(bool wrap) {
    if (activeBuffer) activeBuffer->SetWordWrap(wrap);
}

bool Screen::IsModified() const {
    if (activeBuffer) return activeBuffer->IsModified();
    return false;
}
