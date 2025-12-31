#include "menubar.hpp"
#include "../findreplace/findreplacedialog.hpp"

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

    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(ID_FIND_REPLACE, "Find and Replace...\tCtrl+F");

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    Append(menuFile, "&File");
    Append(menuEdit, "&Edit");
    Append(menuHelp, "&Help");
}
