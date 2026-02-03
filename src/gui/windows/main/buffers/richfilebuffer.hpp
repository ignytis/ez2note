#ifndef GUI_WINDOWS_MAIN_BUFFERS_RICHFILEBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_RICHFILEBUFFER_HPP

#include <wx/stc/stc.h>

#include "abstractfilebuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

/**
 * RichFileBuffer is a file buffer that uses wxStyledTextCtrl
 * to provide advanced text editing features.
 */
class RichFileBuffer : public AbstractFileBuffer {
   public:
    RichFileBuffer(wxWindow* parent, Ez2note::Config& config,
                   const wxString& filePath = "");
    virtual ~RichFileBuffer() = default;

    // AbstractFileBuffer implementation
    void Undo() override;
    void Redo() override;
    void SetShowLineNumbers(bool show) override;
    void SetWordWrap(bool wrap) override;
    bool IsModified() const override;

    bool LoadFile(const wxString& path) override;
    bool SaveFile() override;
    bool SaveFileAs(const wxString& path) override;

    wxStyledTextCtrl* GetTextEdit() const { return textEdit; }

   protected:
    wxStyledTextCtrl* textEdit;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_RICHFILEBUFFER_HPP
