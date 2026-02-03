#ifndef GUI_WINDOWS_MAIN_BUFFERS_FILEBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_FILEBUFFER_HPP

#include "abstractbuffer.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

class FileBuffer : public AbstractBuffer {
   public:
    FileBuffer(wxWindow* parent, Ez2note::Config& config,
               const wxString& filePath = "");
    virtual ~FileBuffer() = default;

    bool LoadFile(const wxString& path);
    bool SaveFile();
    bool SaveFileAs(const wxString& path);
    bool HasFile() const;

    // Override from AbstractBuffer
    wxString GetTitle() const override;

   private:
    wxString filePath;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_FILEBUFFER_HPP
