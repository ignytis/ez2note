# ez2note

A simple text editor

## Project status

Early WIP. I DON'T recommend to use it for file editing.
Although some basic features (open, save files) surprisingly work,
there are cruical features missing, like confirmation dialogs.
You might end up corrupting some document by saving it before you really want to.

## Roadmap

- Basic text editing (open, save files)
- Simple tweaks for user convenience
  - Tabulation for multiple lines
- Tab support
- Plugins (auto-discovery; no plugins by default)
- Splitting the window into multiple working areas
- Binary files (some handling is needed for them I guess. Just added this point as a reminder)
- Error handling (failed to save a file?)

## Some few ideas

- Respect the system color theme. Didn't succeed in Fedora Linux as the system always returns `Qt::ColorScheme::Light`
- Replace the system title bar with custom frame. There are some complexities with drag and drop + resizing the frameless window

## Building

### Prerequisites

- C++ compiler
- Qt Framework v6

## Linux

```bash
qmake
make build
```

In case of errors like

> main.cpp:(.text.startup+0x62): undefined reference to `vtable for MainWindow'

Try:

```bash
qmake -project
```

and then repeat the steps above.

__NB:__ this command might add sopme underired adjustments to `.pro` file (e.g. remove some needed attributes). Review the `.pro` file using Git after running this command