#ifndef APP_HPP
#define APP_HPP

#include <QApplication>

#include "config.hpp"

namespace Ez2note {

/** Application logic: parses command line, shows main window. */
class App {
   public:
    /** Runs the application's event loop. Returns the exit code. */
    int Run(QApplication& qtApp);
    Config& getConfig();

   private:
    Config config;
};

}  // namespace Ez2note

#endif  // APP_HPP
