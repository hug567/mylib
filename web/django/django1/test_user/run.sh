#!/bin/bash

#if [ ! -f db.sqlite3 ]; then
#    python3 manage.py migrate
#fi
python3 manage.py runserver 0.0.0.0:9100
