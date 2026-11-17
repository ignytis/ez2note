#include <QApplication>

#include "app.hpp"
#include "constants.hpp"

using namespace Ez2note;

/** Application entry point. */
int main(int argc, char* argv[]) {
    QApplication qtApp(argc, argv);
    QApplication::setApplicationName(EZ2NOTE_APP_NAME);
    QApplication::setApplicationVersion(EZ2NOTE_APP_VERSION);

    App app;
    return app.Run(qtApp);
}
