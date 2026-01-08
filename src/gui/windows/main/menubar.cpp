#include "menubar.hpp"

#include <wx/wx.h>

#include "../findreplace/findreplacedialog.hpp"

using namespace Ez2note::Gui::Windows::Main;

MenuBar::MenuBar(Ez2note::Config &config) : config(config)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_NEW);
    menuFile->Append(wxID_OPEN);
    menuFile->Append(wxID_SAVE);
    menuFile->Append(wxID_SAVEAS);
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu *menuEdit = new wxMenu;
    menuEdit->Append(wxID_UNDO);
    menuEdit->Append(wxID_REDO);
    menuEdit->AppendSeparator();
    menuEdit->Append(ID_MENU_EDIT_FIND_REPLACE, "Find and Replace...\tCtrl+H");

    wxMenu *menuView = new wxMenu;
    menuView->AppendCheckItem(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS, "Show line numbers");
    menuView->Check(ID_MENU_VIEW_TOGGLE_LINE_NUMBERS, config.getBool("showLineNumbers"));
    menuView->AppendCheckItem(ID_MENU_VIEW_TOGGLE_WORD_WRAP, "Word wrap");
    menuView->Check(ID_MENU_VIEW_TOGGLE_WORD_WRAP, config.getBool("wordWrap"));


    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);

    Append(menuFile, "&File");
    Append(menuEdit, "&Edit");
    Append(menuView, "&View");
    Append(menuHelp, "&Help");
}
