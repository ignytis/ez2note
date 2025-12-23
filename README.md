# ez2note

A simple text editor

## Roadmap

- Basic text editing (open, save files)
- Simple tweaks for user convenience
  - Tabulation for multiple lines
- Tab support
- Plugins (auto-discovery; no plugins by default)
- Splitting the window into multiple working areas

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