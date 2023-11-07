#!/bin/bash

export FLASK_DEBUG=1
export FLASK_APP=main.py

flask run -h 10.110.0.3 -p 9200