#!/bin/bash

function main() {
    cur_dir=$(cd $(dirname $BASH_SOURCE[0]); pwd)

    cd ${cur_dir}
    if [ ! -f db.sqlite3 ]; then
        python3 manage.py migrate
    fi
    python3 manage.py runserver 0.0.0.0:9100
}

main $*
