# Project: ez2note

## General instructions

- The project uses wxWidgets framework
- CMake + GNU Make are used to build the project
- The compiled binary `ez2note` is located in `build` directory

## Coding style

- Use the Google C++ Style Guide
- Order alphabetically the source file paths in `CMakeLists.txt`
- Group the `#include` statements, adding an empty line between each group:
  - for `*.cpp` files the corresponding `*.hpp` file is first
  - standard library includes, like `#include <iostream>`
  - third-party includes, like `#include <wx/wx.h>`
  - project includes, like `#include "mywidget.h"`
- Group include statements: global includes e.g. `<MyWidget>` are placed before
  relative includes like `"mywidget.h"`. Groups are separated with empty line.
- Include guards in header files have a `_HPP` suffix and include a path to header file relatively
  to `src` directory. Example: `src/dir/subdir/mywidget.hpp` -> `DIR_SUBDIR_MYWIDGET_HPP`
- Prefer ternary operators instead of if-else blocks with single statements
- Return early if the whole remaining code inside function is if-else statement
- Prefer explicit type declaration over `auto` keyword
- Inside project, prefer relative paths in `#include` statements
- Namespaces are used to organize code into logical units. The structure of namespaces should
  reflect the project's directory structure, e.g. `src/gui/windows/main` directory -> `Ez2note::Gui::Windows::Main`
- Do not delete the `*_dummy()` functions, they are used to prevent clang-format
  from auto-formatting the code below `wxEND_EVENT_TABLE`

### *.cpp files

- Prefer `using namespace <namespace>;` instead of `namespace <namespace> {`

## Validation of result

- Use multi-threaded building when running `make`
- In Unix environments use `./cmd.sh compile` to build the project

## Project structure

- All `*.cpp` and `*.hpp` source files are located in `src` directory
- Source code for windows is in `src/gui/windows/<window name>`. All window-specific components are placed in the same directory
