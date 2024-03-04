#!/bin/bash

CUR_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export DJANGO_SETTINGS_MODULE=test_user.settings

function main() {
    cd $CUR_DIR/..
    echo "pwd: $PWD"
    if [ ! -f db.sqlite3 ]; then
        echo "no db.sqlite3"
        exit 1
    fi
    python3 scripts/user.py
}

main $*
