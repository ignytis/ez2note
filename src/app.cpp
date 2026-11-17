#include "app.hpp"

#include <QCommandLineParser>
#include <QString>
#include <QStringList>

#include "constants.hpp"
#include "gui/windows/main/mainwindow.hpp"

using namespace Ez2note;
using namespace Ez2note::Gui::Windows::Main;

int App::Run(QApplication& qtApp) {
    QCommandLineParser parser;
    parser.setApplicationDescription(EZ2NOTE_APP_DESCRIPTION);
    parser.addHelpOption();
    parser.addPositionalArgument("input file", "input file", "[input file]");
    parser.process(qtApp);

    const QStringList args = parser.positionalArguments();

    MainWindow window(config);
    if (!args.isEmpty()) {
        window.OpenFile(args.first());
    }
    window.show();
    return QApplication::exec();
}

Config& App::getConfig() { return config; }
