# Building the RPM package

## Prerequisites

RPM expects the source archive to exist in the `SOURCES` directory.
Create it using the command below (mind the app version):

```bash
# Project ROOT dir
tar \
    --transform 's,^,ez2note-0.0.1/,' \
    -cvf dist/rpm/SOURCES/ez2note-0.0.1.tar.gz \
    src assets CMakeLists.txt
```

## Building

```bash
# dist/rpm dir
rpmbuild --define "_topdir $PWD" -bb SPECS/ez2note.spec
```

## Verification

The result RPM package should be available in the `RPMS` directory.
Install it:

```bash
# Project ROOT dir
sudo rpm -Uvh ./dist/rpm/RPMS/x86_64/ez2note-0.0.1-1.fc43.x86_64.rpm
```
Now the application could be found in GNOME applications menu.

Also it is available in DNF list:

```bash
dnf list --installed | grep ez2note

ez2note.x86_64                                       0.0.1-1.fc43                          <unknown>
```

To uninstall:

```bash
sudo dnf remove ez2note
```