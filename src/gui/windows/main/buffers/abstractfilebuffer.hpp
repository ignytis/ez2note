#ifndef GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTFILEBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTFILEBUFFER_HPP

#include "abstractbuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

/**
 * AbstractFileBuffer is a base class for all file buffers.
 * There might be different kinds of file buffers, like simple or rich text
 * editor. The main point is that this kind of buffer is associated with a file.
 */
class AbstractFileBuffer : public AbstractBuffer {
   public:
    AbstractFileBuffer(wxWindow* parent, Ez2note::Config& config,
                       const wxString& filePath = "");
    virtual ~AbstractFileBuffer() = default;

    virtual void Undo() = 0;
    virtual void Redo() = 0;
    virtual void SetShowLineNumbers(bool show) = 0;
    virtual void SetWordWrap(bool wrap) = 0;
    virtual bool IsModified() const = 0;

    virtual bool LoadFile(const wxString& path) = 0;
    virtual bool SaveFile() = 0;
    virtual bool SaveFileAs(const wxString& path) = 0;
    virtual bool HasFile() const;

    wxString GetTitle() const override;

   protected:
    wxString filePath;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTFILEBUFFER_HPP
