#include <wx/wx.h>

#include "../findreplace/findreplacedialog.hpp"
#include "menubar.hpp"

using namespace Ez2note::Gui::Windows::Main;

MenuBar::MenuBar()
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_NEW);
    menuFile->Append(wxID_OPEN);
    menuFile->Append(wxID_SAVE);
    menuFile->Append(wxID_SAVEAS);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuView = new wxMenu;
    menuView->AppendCheckItem(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS, "Show line numbers");
    menuView->AppendCheckItem(ID_MENU_VIEW_TOGGLE_WORD_WRAP, "Word wrap");

    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_MENU_EDIT_FIND_REPLACE, "Find and Replace...\tCtrl+F");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    Append(menuFile, "&File");
    Append(menuView, "&View");
    Append(menuEdit, "&Edit");
    Append(menuHelp, "&Help");
}
