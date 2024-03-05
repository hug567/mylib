#!/bin/bash

CUR_DIR=$(cd $(dirname $BASH_SOURCE[0]); pwd)
export DJANGO_SETTINGS_MODULE=test_user.settings
export PYTHONPATH="$(cd $CUR_DIR/..; pwd):$PYTHONPATH"

function create_superuser() {
    local user="root"
    local password="rootroot"
    local email="root@example.com"

    if [ -f db.sqlite3 ]; then
        return
    fi
    python3 manage.py migrate

    PS1="[host] $ "
    echo $PS1
expect <<EOF
    set timeout 10
    spawn python3 manage.py createsuperuser --username $user --email $email
    expect {
        "Password:" {send "$password\r"; exp_continue}
        "Password (again):" {send "$password\r"; exp_continue}
        "*\[host\] $ *" {}
        timeout {exit 1}
    }
EOF
}

function main() {
    cd $CUR_DIR/..
    create_superuser
    python3 scripts/user.py
}

main $*
