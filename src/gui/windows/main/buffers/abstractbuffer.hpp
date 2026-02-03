#ifndef GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP

#include <wx/stc/stc.h>
#include <wx/wx.h>

#include "../../../../config.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

class AbstractBuffer : public wxPanel {
   public:
    AbstractBuffer(wxWindow* parent, Ez2note::Config& config);
    virtual ~AbstractBuffer() = default;

    virtual void Undo();
    virtual void Redo();
    virtual void SetShowLineNumbers(bool show);
    virtual void SetWordWrap(bool wrap);
    virtual bool IsModified() const;
    virtual wxString GetTitle() const = 0;

    wxStyledTextCtrl* GetTextEdit() const { return textEdit; }

   protected:
    wxStyledTextCtrl* textEdit;
    Ez2note::Config& config;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP
