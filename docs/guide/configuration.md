# Configuration

## Home directory

The home directory might be specified using the `EZ2NOTE_HOME` environment variable.

If not provided, the default home directory falls back to
- Linux:  `~/.ez2note/`

## Configuration file

Configuration file is stored in JSON format in `(HOME_DIR)/config.json`.

## Example file

```json
{
    "editor.showLineNumbers": true,
    "editor.wordWrap": true
}
```

## Configuration keys

### Editor

- `editor.showLineNumbers` (bool) - Show line numbers
- `editor.wordWrap` (bool) - Word wrap