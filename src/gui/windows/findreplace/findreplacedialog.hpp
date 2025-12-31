#ifndef GUI_WINDOWS_FINDREPLACE_FINDREPLACEDIALOG_HPP
#define GUI_WINDOWS_FINDREPLACE_FINDREPLACEDIALOG_HPP

#include <wx/wx.h>
#include <wx/stc/stc.h>

#define ID_FIND_REPLACE 100

namespace Ez2note {
namespace Gui {
namespace Windows {
namespace FindReplace {

class FindReplaceDialog : public wxDialog {
public:
    FindReplaceDialog(wxWindow *parent, wxStyledTextCtrl *textEdit);

private:
    void OnFind(wxCommandEvent &event);
    void OnReplace(wxCommandEvent &event);
    void OnReplaceAll(wxCommandEvent &event);
    void OnCancel(wxCommandEvent &event);

    wxStyledTextCtrl *textEdit;
    wxTextCtrl *findText;
    wxTextCtrl *replaceText;

    wxDECLARE_EVENT_TABLE();
};

}
}
}
}

#endif // GUI_WINDOWS_FINDREPLACE_FINDREPLACEDIALOG_HPP
