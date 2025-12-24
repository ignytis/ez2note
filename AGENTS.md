# Project: ez2note

## General instructions

- The project uses Qt framework. Use `qmake` to build the project
- The compiled binary `ez2note` is located in `build` directory

## Coding style

- Follow the Qt Coding Style
- Order the `#include` statements alphabetically. Group include statements: global includes e.g. `<QWidget>` are placed before relative includes like `"mywidget.h"`
- Include guards in header files have a `_H` suffix and include a path to header file relatively to `src` directory. Example: `src/dir/subdir/mywidget.h` -> `DIR_SUBDIR_MYWIDGET_H`
- Prefer includes `#include <QSomeWidget>` over forward declarations

## Project structure

- All *.cpp and *.h source files are located in `src` directory
- Source code for windows is in `src/gui/windows/<window name>`. All window-specific components are placed in the same directory