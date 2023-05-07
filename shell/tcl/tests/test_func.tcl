#!/usr/bin/tclsh

# without args and return value
proc test_hello {} {
    puts "hello world";  # annotation and commands in the same line
}

# with args
proc test_print_info {name age} {
    puts "people name: $name, age: $age"
}

# with retuen value
proc test_add {a b} {
    set sum [expr $a + $b]
    return $sum
}

proc main {} {
    # function call
    test_hello
    test_print_info Bob 18
    puts "2 + 3 = [test_add 2 3]"
}

main
