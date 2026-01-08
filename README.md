# ez2note

A simple text editor

## Project status

Early WIP. I DON'T recommend to use it for file editing.
Although some basic features (open, save files) surprisingly work,
there are cruical features missing, like confirmation dialogs.
You might end up corrupting some document by saving it before you really want to.

## Roadmap

- Simple tweaks for user convenience
  - Tabulation for multiple lines
- Tab support
- Plugins (auto-discovery; no plugins by default)
- Splitting the window into multiple working areas
- Binary files (some handling is needed for them I guess. Just added this point as a reminder)

## Some few ideas

- Respect the system color theme. Didn't succeed in Fedora Linux as the system always returns `Qt::ColorScheme::Light`
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

### Building

```bash
make -j"$(nproc)"
```
