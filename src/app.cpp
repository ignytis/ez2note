#include "app.hpp"

#include <wx/cmdline.h>

#include "gui/windows/main/mainwindow.hpp"

using namespace Ez2note;
using namespace Ez2note::Gui::Windows::Main;

static const wxCmdLineEntryDesc CMD_LINE_DESC[] = {
    {wxCMD_LINE_PARAM, NULL, NULL, "input file", wxCMD_LINE_VAL_STRING,
     wxCMD_LINE_PARAM_OPTIONAL},
    {wxCMD_LINE_SWITCH, "h", "help", "show this help message",
     wxCMD_LINE_VAL_NONE, wxCMD_LINE_OPTION_HELP},
    {wxCMD_LINE_NONE}};

bool App::OnInit() {
    wxCmdLineParser parser(CMD_LINE_DESC, argc, argv);
    parser.SetSwitchChars(wxT("-"));

    int ret = parser.Parse(true);
    if (ret != 0) {
        // -1 means error, 1 means help was shown
        return false;
    }

    wxString m_fileName;
    if (parser.GetParamCount() > 0) {
        m_fileName = parser.GetParam(0);
    }

    MainWindow* window = new MainWindow(config);
    if (!m_fileName.IsEmpty()) {
        window->OpenFile(m_fileName);
    }
    window->Show(true);
    return true;
}

Config& App::getConfig() { return config; }
