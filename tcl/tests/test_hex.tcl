#!/usr/bin/tclsh

puts "hello world"

for {set i 0} {$i<256} {incr i} {
    puts "i = $i"
    #puts hex($i).upper()[2:]
    #print(hex($i).upper()[2:])
}
