#!/usr/bin/env bash

set -euo pipefail

# Prerequisites: check if jq is installed
if ! command -v jq &> /dev/null; then
    echo "Error: jq is not installed" >&2
    exit 1
fi

appVersion=$(jq -r .version ./project.json)

# Create source archive
tar --transform "s,^,ez2note-$appVersion/," \
    -cvf dist/rpm/SOURCES/ez2note-$appVersion.tar.gz \
    src assets CMakeLists.txt project.json

pushd dist/rpm

# Build RPM package
rpmbuild \
    --define "_topdir $PWD" \
    --define "_app_version $appVersion" \
    -bb SPECS/ez2note.spec

popd
