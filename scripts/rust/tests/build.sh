#!/bin/bash

SRCDIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
BUILDDIR=$(pwd)

SRCFILES=(
    test_print.rs
    test_var.rs
)

function main() {
    if [ "$SRCDIR" == "$BUILDDIR" ]; then
        echo "cannot build in source dir"
        exit 1
    fi
    for f in ${SRCFILES[@]}; do
        echo "rustc $SRCDIR/$f"
        rustc $SRCDIR/$f
    done
}

main *
