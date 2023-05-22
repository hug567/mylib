#!/usr/bin/tclsh

puts "hello world"

for {set i 0} {$i<256} {incr i} {
    set x [format "%x" $i]
    puts "x = $x"
}
