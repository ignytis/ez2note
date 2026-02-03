#ifndef GUI_WINDOWS_MAIN_SCREEN_HPP
#define GUI_WINDOWS_MAIN_SCREEN_HPP

#include <wx/wx.h>

#include <vector>

#include "../../../config.hpp"
#include "buffers/abstractbuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {

class Screen : public wxPanel {
   public:
    Screen(wxWindow* parent, Ez2note::Config& config);
    virtual ~Screen();

    Buffers::AbstractBuffer* OpenNewFile();
    Buffers::AbstractBuffer* OpenFile(const wxString& filePath);
    void CloseBuffer(Buffers::AbstractBuffer* buffer);

    Buffers::AbstractBuffer* GetActiveBuffer() const;
    void SetActiveBuffer(Buffers::AbstractBuffer* buffer);

    // Forwarding methods
    void Undo();
    void Redo();
    void SetShowLineNumbers(bool show);
    void SetWordWrap(bool wrap);
    bool IsModified() const;

   private:
    void UpdateLayout();

    std::vector<Buffers::AbstractBuffer*> buffers;
    Buffers::AbstractBuffer* activeBuffer;
    Ez2note::Config& config;
    wxBoxSizer* sizer;
};

}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_SCREEN_HPP
