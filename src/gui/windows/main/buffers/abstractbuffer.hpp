#ifndef GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP

#include <wx/wx.h>

#include "../../../../config.hpp"
#include "../../abstractmenu.hpp"

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace Main {
namespace Buffers {

/**
 * AbstractBuffer is a base class for all buffers.
 * Buffer can show file edit in the text editor or theoretically
 * could display anything else (HEX editor? Terminal?)
 */
class AbstractBuffer : public wxPanel {
   public:
    AbstractBuffer(wxWindow* parent, Ez2note::Config& config);
    virtual ~AbstractBuffer() = default;

    virtual wxString GetTitle() const = 0;
    virtual AbstractMenu* GetMenu() = 0;

   protected:
    Ez2note::Config& config;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_ABSTRACTBUFFER_HPP
