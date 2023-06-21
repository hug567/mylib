#!/bin/bash

#function myname() {
#    echo "[test01.sh] myname: $0"
#}

function test01_main() {( # 子shell
    function myname() {
        echo "[test01.sh] myname: $0"
    }
    myname
)}
