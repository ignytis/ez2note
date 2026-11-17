# Building the RPM package

From root directory of the project run:

```bash
bash ./dist/rpm/build.sh
```

## Verification

The result RPM package should be available in the `RPMS` directory.

The package built by `build.sh` is **not signed**. Recent RPM versions (6.x, Fedora 45+)
refuse to install such a package with the error:

```
package ez2note-3.0.0-1.fc45.x86_64 does not verify: no signature
```

There are two ways to deal with it.

### Quick way: skip the signature check

Fine for a package built and installed on the same machine (local build).
Install it (mind the version):

```bash
sudo rpm -Uvh --nosignature ./dist/rpm/RPMS/x86_64/ez2note-3.0.0-1.fc45.x86_64.rpm
```

### Proper way: sign the package

Recommended if the package is distributed to other machines.

1. Sign the package with your GPG key:

    ```bash
    rpmsign --define "_gpg_name <key id>" --addsign ./dist/rpm/RPMS/x86_64/ez2note-3.0.0-1.fc45.x86_64.rpm
    ```

2. Export the public key (`gpg --armor --export <key id> > ez2note.asc`) and import it
   on the target machine:

    ```bash
    sudo rpm --import ez2note.asc
    ```

3. Check the signature and install as usual, without `--nosignature`:

    ```bash
    rpm -K ./dist/rpm/RPMS/x86_64/ez2note-3.0.0-1.fc45.x86_64.rpm
    sudo rpm -Uvh ./dist/rpm/RPMS/x86_64/ez2note-3.0.0-1.fc45.x86_64.rpm
    ```

Now the application could be found in GNOME applications menu.

Also it is available in DNF list:

```bash
dnf list --installed | grep ez2note

ez2note.x86_64                                       3.0.0-1.fc45                          <unknown>
```

To uninstall:

```bash
sudo dnf remove ez2note
```