#include "screen.hpp"

#include "buffers/abstractfilebuffer.hpp"
#include "buffers/richfilebuffer.hpp"

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
    Buffers::RichFileBuffer* newBuffer =
        new Buffers::RichFileBuffer(this, config);
    buffers.push_back(newBuffer);
    SetActiveBuffer(newBuffer);
    return newBuffer;
}

Buffers::AbstractBuffer* Screen::OpenFile(const wxString& filePath) {
    Buffers::RichFileBuffer* newBuffer =
        new Buffers::RichFileBuffer(this, config, filePath);
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
    Buffers::AbstractFileBuffer* fileBuffer =
        dynamic_cast<Buffers::AbstractFileBuffer*>(activeBuffer);
    if (fileBuffer) fileBuffer->Undo();
}

void Screen::Redo() {
    Buffers::AbstractFileBuffer* fileBuffer =
        dynamic_cast<Buffers::AbstractFileBuffer*>(activeBuffer);
    if (fileBuffer) fileBuffer->Redo();
}

void Screen::SetShowLineNumbers(bool show) {
    Buffers::AbstractFileBuffer* fileBuffer =
        dynamic_cast<Buffers::AbstractFileBuffer*>(activeBuffer);
    if (fileBuffer) fileBuffer->SetShowLineNumbers(show);
}

void Screen::SetWordWrap(bool wrap) {
    Buffers::AbstractFileBuffer* fileBuffer =
        dynamic_cast<Buffers::AbstractFileBuffer*>(activeBuffer);
    if (fileBuffer) fileBuffer->SetWordWrap(wrap);
}

bool Screen::IsModified() const {
    Buffers::AbstractFileBuffer* fileBuffer =
        dynamic_cast<Buffers::AbstractFileBuffer*>(activeBuffer);
    if (fileBuffer) return fileBuffer->IsModified();
    return false;
}
