#ifndef GUI_WINDOWS_MAIN_SCREEN_HPP
#define GUI_WINDOWS_MAIN_SCREEN_HPP

#include <wx/aui/aui.h>
#include <wx/wx.h>

#include <vector>

#include "../../../config.hpp"
#include "buffers/abstractbuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {

wxDECLARE_EVENT(DATA_BUFFER_CHANGED, wxCommandEvent);

/**
 * Screen is a container for buffers.
 * Currently, the application can have only one screen with one buffer inside.
 */
class Screen : public wxPanel {
   public:
    Screen(wxWindow* parent, Ez2note::Config& config);
    virtual ~Screen();

    void AddBuffer(Buffers::AbstractBuffer* buffer);
    void SplitBuffer(Buffers::AbstractBuffer* buffer, wxDirection direction);
    void CloseBuffer(Buffers::AbstractBuffer* buffer);

    Buffers::AbstractBuffer* GetActiveBuffer() const;
    void SetActiveBuffer(Buffers::AbstractBuffer* buffer);

   private:
    void UpdateLayout();

    void OnBufferChanged(wxCommandEvent& event);
    void OnPaneClose(wxAuiManagerEvent& event);
    void OnPaneActivated(wxAuiManagerEvent& event);

    wxFrame* mainWindow;  // Main Window
    std::vector<Buffers::AbstractBuffer*> buffers;
    Buffers::AbstractBuffer* activeBuffer;
    Ez2note::Config& config;
    wxAuiManager m_mgr;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_SCREEN_HPP
