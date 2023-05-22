#!/usr/bin/tclsh

proc test_add {} {
    puts "test_add: ----------------------------------------------------"
    # int
    puts "1 + 2 = [expr 1 + 2]"
    puts "1 + 0 = [expr 1 + 0]"
    puts "1 + -3 = [expr 1 + -3]"
    puts "-3 + 5 = [expr -3 + 5]"
    # float
    puts "1.2 + 3.4 = [expr 1.2 + 3.4]"
}

proc test_sub {} {
    puts "test_sub: ----------------------------------------------------"
    # int
    puts "3 - 2 = [expr 3 - 2]"
    puts "3 - 0 = [expr 3 - 0]"
    puts "3 - -5 = [expr 3 - -5]"
    puts "-3 - 2 = [expr -3 - 2]"
    # float
    puts "1.2 - 3.4 = [expr 1.2 - 3.4]"
}

proc test_mul {} {
    puts "test_mul: ----------------------------------------------------"
    # int
    puts "3 * 2 = [expr 3 * 2]"
    puts "3 * 0 = [expr 3 * 0]"
    puts "3 * -5 = [expr 3 * -5]"
    puts "-3 * -2 = [expr -3 * -2]"
    # float
    puts "1.2 * 3.4 = [expr 1.2 *3.4]"
}

proc test_div {} {
    puts "test_div: ----------------------------------------------------"
    # int
    puts "3 / 2 = [expr 3 / 2]"
    puts "0 / 3 = [expr 0 / 3]"
    puts "-5 / 2 = [expr -5 / 2]"
    puts "-7 / -2 = [expr -7 / -2]"
    # float
    puts "5.0 / 2 = [expr 5.0 / 2]"
    puts "10.0 / 3 = [expr 10.0 / 3]"
}

proc test_mod {} {
    puts "test_mod: ----------------------------------------------------"
    # int
    puts "3 % 2 = [expr 3 % 2]"
    puts "0 % 3 = [expr 0 % 3]"
    puts "-5 % 2 = [expr -5 % 2]"
    puts "-7 % -2 = [expr -7 % -2]"
    puts "9 % -2 = [expr 9 % -2]"
}

proc test_math_lib {} {
    puts "test_math_lib: -----------------------------------------------"
    puts "abs(-3) = [expr abs(-3)]"
    puts "sin(60) = [expr sin(60)]"
    puts "pow(2,3) = [expr pow(2,3)]"
    puts "exp(0) = [expr exp(0)]"
}

proc main {} {
    test_add
    test_sub
    test_mul
    test_div
    test_mod
    test_math_lib
}

main
