#include "screen.hpp"

#include <wx/event.h>

#include "buffers/richfilebuffer.hpp"

using namespace Ez2note::Gui::Windows::Main;

wxDEFINE_EVENT(Ez2note::Gui::Windows::Main::DATA_BUFFER_CHANGED,
               wxCommandEvent);

Screen::Screen(wxWindow* parent, Ez2note::Config& config)
    : wxPanel(parent, wxID_ANY),
      mainWindow(dynamic_cast<wxFrame*>(parent)),
      activeBuffer(nullptr),
      config(config) {
    sizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(sizer);

    Bind(DATA_BUFFER_CHANGED, &Screen::OnBufferChanged, this);

    // Create initial buffer
    Buffers::RichFileBuffer* initialBuffer =
        new Buffers::RichFileBuffer(this, mainWindow, config);
    AddBuffer(initialBuffer);
}

Screen::~Screen() {
    // Buffers are children of this window, so they are deleted automatically by
    // wxWidgets. We just need to clear the vector to avoid dangling pointers if
    // we accessed them in destructor later (though we don't).
    buffers.clear();
}

void Screen::AddBuffer(Buffers::AbstractBuffer* buffer) {
    buffers.push_back(buffer);
    SetActiveBuffer(buffer);
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

void Screen::OnBufferChanged(wxCommandEvent& event) {
    wxPostEvent(mainWindow, event);
}

Buffers::AbstractBuffer* Screen::GetActiveBuffer() const {
    return activeBuffer;
}

void Screen::SetActiveBuffer(Buffers::AbstractBuffer* buffer) {
    activeBuffer = buffer;
    UpdateLayout();

    wxCommandEvent event(DATA_BUFFER_CHANGED);
    event.SetEventObject(this);
    ProcessWindowEvent(event);
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
