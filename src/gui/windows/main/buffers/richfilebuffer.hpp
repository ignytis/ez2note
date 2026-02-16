#ifndef GUI_WINDOWS_MAIN_BUFFERS_RICHFILEBUFFER_HPP
#define GUI_WINDOWS_MAIN_BUFFERS_RICHFILEBUFFER_HPP

#include <wx/event.h>
#include <wx/stc/stc.h>

#include "abstractfilebuffer.hpp"

// Define custom events for buffer activation/deactivation
wxDECLARE_EVENT(EZ_EVT_BUFFER_ACTIVATED, wxCommandEvent);
wxDECLARE_EVENT(EZ_EVT_BUFFER_DEACTIVATED, wxCommandEvent);

#define ID_MENU_VIEW_TOGGLE_LINE_NUMBERS 101
#define ID_MENU_VIEW_TOGGLE_WORD_WRAP 102
#define ID_MENU_VIEW_SPLIT_HORIZONTAL 103
#define ID_MENU_VIEW_SPLIT_VERTICAL 104

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
    RichFileBuffer(wxWindow* parent, wxFrame* mainFrame,
                   Ez2note::Config& config, const wxString& filePath = "");
    virtual ~RichFileBuffer() = default;

    // AbstractFileBuffer implementation
    void Undo() override;
    void Redo() override;
    void SetShowLineNumbers(bool show);
    void SetWordWrap(bool wrap);
    bool IsModified() const override;

    bool LoadFile(const wxString& path) override;
    bool SaveFile() override;
    bool SaveFileAs(const wxString& path) override;

    wxStyledTextCtrl* GetTextEdit() const { return textEdit; }
    AbstractMenu* GetMenu() override;

    // Event handlers
    void OnBufferActivated(wxCommandEvent& event);
    void OnBufferDeactivated(wxCommandEvent& event);
    void OnNew(wxCommandEvent& event);
    void OnOpen(wxCommandEvent& event);
    void OnSave(wxCommandEvent& event);
    void OnSaveAs(wxCommandEvent& event);
    void OnUndo(wxCommandEvent& event);
    void OnRedo(wxCommandEvent& event);
    void OnFindReplace(wxCommandEvent& event);
    void OnToggleLineNumbers(wxCommandEvent& event);
    void OnToggleWordWrap(wxCommandEvent& event);
    void OnSplitHorizontal(wxCommandEvent& event);
    void OnSplitVertical(wxCommandEvent& event);
    void OnTextEditClick(wxMouseEvent& event);
    void OnTextEditFocus(wxFocusEvent& event);
    void SetFocusToBuffer();

    class MenuBar : public AbstractMenu {
       public:
        MenuBar(Ez2note::Config& config);
    };

   protected:
    wxStyledTextCtrl* textEdit;
    MenuBar* menuBar;
};

}  // namespace Buffers
}  // namespace Main
}  // namespace Windows
}  // namespace Gui
}  // namespace Ez2note

#endif  // GUI_WINDOWS_MAIN_BUFFERS_RICHFILEBUFFER_HPP
