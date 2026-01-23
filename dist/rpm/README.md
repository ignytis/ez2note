# Building the RPM package

From root directory of the project run:

```bash
bash ./dist/rpm/build.sh
```

## Verification

The result RPM package should be available in the `RPMS` directory.
Install it (mind the version):

```bash
sudo rpm -Uvh ./dist/rpm/RPMS/x86_64/ez2note-1.0.0-1.fc43.x86_64.rpm
```
Now the application could be found in GNOME applications menu.

Also it is available in DNF list:

```bash
dnf list --installed | grep ez2note

ez2note.x86_64                                       1.0.0-1.fc43                          <unknown>
```

To uninstall:

```bash
sudo dnf remove ez2note
```