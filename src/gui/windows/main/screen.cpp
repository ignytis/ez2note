#include "screen.hpp"

#include <wx/event.h>
#include <wx/log.h>

#include "buffers/richfilebuffer.hpp"

using namespace Ez2note::Gui::Windows::Main;

wxDEFINE_EVENT(Ez2note::Gui::Windows::Main::DATA_BUFFER_CHANGED,
               wxCommandEvent);

Screen::Screen(wxWindow* parent, Ez2note::Config& config)
    : wxPanel(parent, wxID_ANY),
      mainWindow(dynamic_cast<wxFrame*>(parent)),
      activeBuffer(nullptr),
      config(config) {
    m_mgr.SetManagedWindow(this);

    Bind(DATA_BUFFER_CHANGED, &Screen::OnBufferChanged, this);
    Bind(wxEVT_AUI_PANE_CLOSE, &Screen::OnPaneClose, this);
    Bind(wxEVT_AUI_PANE_ACTIVATED, &Screen::OnPaneActivated, this);

    // Create initial buffer
    Buffers::RichFileBuffer* initialBuffer =
        new Buffers::RichFileBuffer(this, mainWindow, config);

    wxAuiPaneInfo info =
        wxAuiPaneInfo().CenterPane().Caption("Buffer").CloseButton(true).Name(
            "InitialBuffer");

    AddBuffer(initialBuffer);
    m_mgr.AddPane(initialBuffer, info);
    info.Show();

    m_mgr.Update();
}

Screen::~Screen() {
    m_mgr.UnInit();
    // Buffers are children of this window, so they are deleted automatically by
    // wxWidgets. We just need to clear the vector to avoid dangling pointers.
    buffers.clear();
}

void Screen::AddBuffer(Buffers::AbstractBuffer* buffer) {
    buffers.push_back(buffer);
    SetActiveBuffer(buffer);
}

void Screen::SplitBuffer(Buffers::AbstractBuffer* buffer,
                         wxDirection direction) {
    // Create new buffer
    Buffers::RichFileBuffer* newBuffer =
        new Buffers::RichFileBuffer(this, mainWindow, config);

    // Allow the new buffer to share the file content if the existing buffer has
    // a file? For now, just create a new empty buffer or load same file if
    // needed. The user requirement doesn't specify cloning, just "splittable".
    // We'll mimic Emacs somewhat by trying to open the same file if possible?
    // Or just empty. Let's start with empty for safety and simplicity.

    wxAuiPaneInfo info;
    info.CloseButton(false)
        .DestroyOnClose(false)
        .Dockable(false)
        .Movable(false)
        .CaptionVisible(false);

    if (direction == wxRIGHT) {
        info.Right();
    } else if (direction == wxBOTTOM) {
        info.Bottom();
    }
    // Note: Center() is usually reserved for the "content", AUI requires one
    // Center pane. If we want multiple equal panes, we might need them all to
    // be Center? Or just use docking. Default docking is fine for now.

    m_mgr.AddPane(newBuffer, info);
    AddBuffer(newBuffer);
    m_mgr.Update();
}

void Screen::CloseBuffer(Buffers::AbstractBuffer* buffer) {
    // Find and remove from vector
    for (std::vector<Buffers::AbstractBuffer*>::iterator it = buffers.begin();
        it != buffers.end(); ++it) {
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
            wxCommandEvent event(EZ_EVT_BUFFER_DEACTIVATED);
            event.SetEventObject(activeBuffer);
            activeBuffer->GetEventHandler()->ProcessEvent(event);

            activeBuffer = nullptr;
        }
    }

    // Detach from manager
    m_mgr.DetachPane(buffer);

    // Destroy the window
    buffer->Destroy();

    m_mgr.Update();
}

void Screen::OnBufferChanged(wxCommandEvent& event) {
    wxPostEvent(mainWindow, event);
}

Buffers::AbstractBuffer* Screen::GetActiveBuffer() const {
    return activeBuffer;
}

void Screen::SetActiveBuffer(Buffers::AbstractBuffer* buffer) {
    if (activeBuffer && activeBuffer != buffer) {
        wxCommandEvent event(EZ_EVT_BUFFER_DEACTIVATED);
        event.SetEventObject(activeBuffer);
        activeBuffer->GetEventHandler()->ProcessEvent(event);
    }

    activeBuffer = buffer;

    // AUI ensures visibility if managed
    if (buffer) {
        wxAuiPaneInfo& info = m_mgr.GetPane(buffer);
        if (info.IsOk()) {
            info.Show();
            // We don't necessarily want to force layout update every time we
            // just set active pointer unless we want to highlight it.
        }

        wxCommandEvent event(EZ_EVT_BUFFER_ACTIVATED);
        event.SetEventObject(buffer);
        buffer->GetEventHandler()->ProcessEvent(event);
    }

    wxCommandEvent event(DATA_BUFFER_CHANGED);
    event.SetEventObject(this);
    ProcessWindowEvent(event);
}

void Screen::UpdateLayout() { m_mgr.Update(); }

void Screen::OnPaneClose(wxAuiManagerEvent& event) {
    Buffers::AbstractBuffer* buffer =
        dynamic_cast<Buffers::AbstractBuffer*>(event.GetPane()->window);
    if (buffer) {
        // We handle destruction.
        // Prevent AUI from destroying it immediately if we want to do it in
        // CloseBuffer But event.GetPane().window is the window. If we let AUI
        // destroy it, we just need to clean up our references. But CloseBuffer
        // calls m_mgr.DetachPane. Let's vetobe the event and call CloseBuffer?
        // Or better: let CloseBuffer handle everything.
        // m_mgr.DetachPane is needed.

        // If we Veto, the pane stays.
        // If we don't Veto, the pane closes (hides) but window is not destroyed
        // unless DestroyOnClose is set. We set DestroyOnClose(false) in
        // SplitBuffer/Constructor (default is false). So pane is just hidden.
        // We want to actually destroy it.

        // Let's schedule CloseBuffer.
        // We cannot destroy the window immediately inside the event handler
        // sometimes. But CloseBuffer calls Destroy().

        CloseBuffer(buffer);
        event.Veto();  // We manually removed and destroyed it.
    }
}

void Screen::OnPaneActivated(wxAuiManagerEvent& event) {
    Buffers::AbstractBuffer* buffer =
        dynamic_cast<Buffers::AbstractBuffer*>(event.GetPane()->window);
    if (buffer) {
        SetActiveBuffer(buffer);
    }
}
