#include "app.hpp"

App::App(int argc, char *argv[])
    : QApplication(argc, argv)
{
    QApplication::setApplicationName(APP_NAME);
    QApplication::setApplicationVersion(APP_VERSION);
}

int App::exec()
{
    QCommandLineParser parser;
    parser.setApplicationDescription(APP_DESCRIPTION);
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addPositionalArgument("file", "The file to open.");
    parser.process(*this);

    const QStringList args = parser.positionalArguments();
    MainWindow window(args.isEmpty() ? "" : args.first());
    window.resize(800, 600);
    window.show();
    return QApplication::exec();
}