# ez2note

A simple text editor

## Project status

WIP. Basic features work.

## User guide

See [docs/guide/](docs/guide/).

## Roadmap

- Tab support
- Plugins (auto-discovery; no plugins by default)
- Splitting the window into multiple working areas
- Binary files (some handling is needed for them I guess. Just added this point as a reminder)

## Some few ideas

- Respect the system color theme
- Replace the system title bar with custom frame. There are some complexities with drag and drop + resizing the frameless window

## Building

### Prerequisites

- C++ compiler
- wxWidgets development library
- CMake >= 3.16

## Linux

### Initialization of the project

```bash
cmake -DCMAKE_BUILD_TYPE=DEBUG .
```

## Windows

Open the project as a CMake project in Visual Studio. It should generate the project files.
To build the project, use the `Build` menu.

Dependencies (like wxWidgets) could be installed using vcpkg.

### Building

```bash
make -j"$(nproc)"
```
