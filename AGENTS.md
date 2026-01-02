# Project: ez2note

## General instructions

- The project uses wxWidgets framework
- CMake + GNU Make are used to build the project
- The compiled binary `ez2note` is located in `build` directory

## Coding style

- Order alphabetically such lists as:
  - `#include` statements
  - File lists in `CMakeLists.txt`
- Group include statements: global includes e.g. `<MyWid>` are placed before relative includes like `"mywidget.h"`. Groups are separated with empty line.
- Include guards in header files have a `_HPP` suffix and include a path to header file relatively to `src` directory. Example: `src/dir/subdir/mywidget.hpp` -> `DIR_SUBDIR_MYWIDGET_HPP`
- Prefer includes `#include <SomeWidget>` over forward declarations
- Prefer ternary operators instead of if-else blocks with single statements
- Return early if the whole remaining code inside function is if-else statement
- Prefer explicit type declaration over `auto` keyword
- Inside project, prefer relative paths in `#include` statements

## Project structure

- All *.cpp and *.h source files are located in `src` directory
- Source code for windows is in `src/gui/windows/<window name>`. All window-specific components are placed in the same directory
