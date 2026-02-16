#include "abstractfilebuffer.hpp"

#include <wx/filename.h>

#include "../../../../constants.hpp"

using namespace Ez2note::Gui::Windows::Main::Buffers;

int Ez2note::Gui::Windows::Main::Buffers::showDocumentModifiedDialog() {
    return wxMessageBox(
        "The document has been modified.\nDo you want to save your "
        "changes?",
        EZ2NOTE_APP_NAME, wxYES_NO | wxCANCEL);
}

AbstractFileBuffer::AbstractFileBuffer(wxWindow* parent, wxFrame* mainFrame,
                                       Ez2note::Config& config,
                                       const wxString& filePath)
    : AbstractBuffer(parent, config),
      filePath(filePath),
      mainFrame(mainFrame) {}

bool AbstractFileBuffer::HasFile() const { return !filePath.IsEmpty(); }

wxString AbstractFileBuffer::GetTitle() const {
    if (filePath.IsEmpty()) {
        return "Untitled";
    }
    wxFileName fileName(filePath);
    return fileName.GetFullName();
}
