#!/usr/bin/env bash

set -eo pipefail

COMMAND=$1

function compile {
    make -j`$(nproc)`
}

function run {
    ./build/ez2note
}

if [ "$COMMAND" = "compile" ]; then
    compile
elif [ "$COMMAND" = "run" ]; then
    run    
elif [ "$COMMAND" = "compile-run" ]; then
    compile
    run
else
    echo "Usage: ./cmd.sh [compile|run|compile-run]"
fi