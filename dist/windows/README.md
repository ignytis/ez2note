# Windows MSI creation

1\. Install [.NET SDK](https://dotnet.microsoft.com/en-us/download)
by downloading an installed from webpage

2\. Install [WiX toolset](https://www.firegiant.com/wixtoolset/) via CLI:
```
dotnet tool install --global wix
```

3\. Install a `WixToolset.UI.wixext` extension:
```
dotnet add package WixToolset.Ui.wixext
```

4\. Add the extension in THIS dir:

```
wix extension add WixToolset.UI.wixext
```

 4\. Build a project
```
 wix build .\ez2note.wxs -ext WixToolset.UI.wixext
```