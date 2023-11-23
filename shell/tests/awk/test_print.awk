#!/usr/bin/awk -f
# run: ./test_print.awk file.txt

BEGIN {
    print "begin awk script......"
}

END {
    print "end awk script......"
}

{
    print $1
}
