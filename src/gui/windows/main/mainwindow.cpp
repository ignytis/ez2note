#include <wx/display.h>
#include <wx/stc/stc.h>
#include <wx/wx.h>

#include "../../../constants.hpp"
#include "../about/aboutwindow.hpp"
#include "../findreplace/findreplacedialog.hpp"
#include "mainwindow.hpp"
#include "menubar.hpp"


using namespace Ez2note::Gui::Windows::About;
using namespace Ez2note::Gui::Windows::FindReplace;
using namespace Ez2note::Gui::Windows::Main;

wxBEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_NEW, MainWindow::OnNew)
    EVT_MENU(wxID_OPEN, MainWindow::OnOpen)
    EVT_MENU(wxID_SAVE, MainWindow::OnSave)
    EVT_MENU(wxID_SAVEAS, MainWindow::OnSaveAs)
    EVT_MENU(wxID_ABOUT, MainWindow::OnAbout)
    EVT_MENU(wxID_EXIT, MainWindow::OnExit)
    EVT_MENU(ID_MENU_EDIT_FIND_REPLACE, MainWindow::OnFindReplace)
    EVT_MENU(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS, MainWindow::OnToggleLineNumbers)
    EVT_CLOSE(MainWindow::OnClose)
wxEND_EVENT_TABLE()


/**
 * Shows a dialog asking the user if they want to save their changes.
 * @return The user's choice (wxID_YES, wxID_NO, or wxID_CANCEL).
 */
int showDocumentModifiedDialog()
{
    return wxMessageBox("The document has been modified.\nDo you want to save your changes?",
                         "ez2note", wxYES_NO | wxCANCEL);
}


MainWindow::MainWindow()
    : wxFrame(NULL, wxID_ANY, EZ2NOTE_APP_NAME)
{
    // By default, set the window size to 1/2 of the screen size
    wxDisplay display;
    this->SetSize(display.GetClientArea().GetSize() / 2);

    SetMenuBar(new MenuBar);

    textEdit = new wxStyledTextCtrl(this, wxID_ANY);
    textEdit->SetMarginWidth(1, 0);
    textEdit->SetMarginType(1, wxSTC_MARGIN_NUMBER);
    textEdit->SetWrapMode(wxSTC_WRAP_WORD);

    CreateStatusBar();
    SetStatusText(wxString::Format("Welcome to %s!", EZ2NOTE_APP_NAME));
}

void MainWindow::OnNew(wxCommandEvent &event)
{
    if (textEdit->IsModified()) {
      switch (showDocumentModifiedDialog())  {
          case wxYES:
              OnSave(event);
              break;
          case wxCANCEL:
              return;
              break;
      }
    }

    textEdit->ClearAll();
    currentFile.Clear();
}

void MainWindow::OnOpen(wxCommandEvent &event)
{
    if (textEdit->IsModified()) {
        switch (showDocumentModifiedDialog())  {
            case wxYES:
                OnSave(event);
                break;
            case wxCANCEL:
                return;
                break;
        }
    }

    wxFileDialog openFileDialog(this, "Open file", "", "",
                                "All files|*", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_CANCEL)
        return;

    OpenFile(openFileDialog.GetPath());
}

void MainWindow::OpenFile(const wxString &filePath)
{
    if (textEdit->LoadFile(filePath)) {
        currentFile = filePath;
    }
}

void MainWindow::doSaveFile()
{
    textEdit->SaveFile(currentFile);
    SetStatusText(wxString::Format("File '%s' saved",currentFile));
}

void MainWindow::doSaveFile(wxString filePath)
{
    currentFile = filePath;
    doSaveFile();
}

void MainWindow::OnSave(wxCommandEvent &event)
{
    if (currentFile.IsEmpty()) {
        OnSaveAs(event);
    } else {
      this->doSaveFile();
    }
}

void MainWindow::OnSaveAs(wxCommandEvent &event)
{
    wxFileDialog saveFileDialog(this, "Save file", "", "",
                                "Text files (*.txt)|*.txt", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);

    if (saveFileDialog.ShowModal() == wxID_CANCEL)
        return;
    this->doSaveFile(saveFileDialog.GetPath());
}

void MainWindow::OnAbout(wxCommandEvent &event)
{
    AboutWindow *about = new AboutWindow(this);
    about->ShowWindowModal();
}

void MainWindow::OnFindReplace(wxCommandEvent &event)
{
    FindReplaceDialog *findReplace = new FindReplaceDialog(this, textEdit);
    findReplace->Show();
}

void MainWindow::OnToggleLineNumbers(wxCommandEvent &event)
{
    if (event.IsChecked())
    {
        textEdit->SetMarginWidth(1, 50);
    }
    else
    {
        textEdit->SetMarginWidth(1, 0);
    }
}

void MainWindow::OnExit(wxCommandEvent &event)
{
    Close(true);
}

void MainWindow::OnClose(wxCloseEvent &event)
{
    if (textEdit->IsModified()) {
        wxCommandEvent saveEvent(wxEVT_COMMAND_MENU_SELECTED, wxID_SAVE);
        switch (showDocumentModifiedDialog()) {
            case wxYES:
                OnSave(saveEvent);
                break;
            case wxCANCEL:
                return;
                break;
        }
    }

    Destroy();
}
