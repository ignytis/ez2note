#include "filebuffer.hpp"

#include <wx/filename.h>

using namespace Ez2note::Gui::Windows::Main::Buffers;

FileBuffer::FileBuffer(wxWindow* parent, Ez2note::Config& config,
                       const wxString& filePath)
    : AbstractBuffer(parent, config), filePath(filePath) {
    if (!filePath.IsEmpty()) {
        LoadFile(filePath);
    }
}

bool FileBuffer::LoadFile(const wxString& path) {
    if (textEdit->LoadFile(path)) {
        filePath = path;
        return true;
    }
    return false;
}

bool FileBuffer::SaveFile() {
    if (filePath.IsEmpty()) {
        return false;
    }
    return textEdit->SaveFile(filePath);
}

bool FileBuffer::SaveFileAs(const wxString& path) {
    if (textEdit->SaveFile(path)) {
        filePath = path;
        return true;
    }
    return false;
}

bool FileBuffer::HasFile() const { return !filePath.IsEmpty(); }

wxString FileBuffer::GetTitle() const {
    if (filePath.IsEmpty()) {
        return "Untitled";
    }
    wxFileName fileName(filePath);
    return fileName.GetFullName();
}
