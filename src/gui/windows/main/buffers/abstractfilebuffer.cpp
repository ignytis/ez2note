#include "abstractfilebuffer.hpp"

#include <wx/filename.h>

using namespace Ez2note::Gui::Windows::Main::Buffers;

AbstractFileBuffer::AbstractFileBuffer(wxWindow* parent,
                                       Ez2note::Config& config,
                                       const wxString& filePath)
    : AbstractBuffer(parent, config), filePath(filePath) {}

bool AbstractFileBuffer::HasFile() const { return !filePath.IsEmpty(); }

wxString AbstractFileBuffer::GetTitle() const {
    if (filePath.IsEmpty()) {
        return "Untitled";
    }
    wxFileName fileName(filePath);
    return fileName.GetFullName();
}
