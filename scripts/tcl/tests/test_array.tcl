#!/usr/bin/tclsh

proc test_array {} {
    puts "test_array: --------------------------------------------------"
    # init array
    for {set i 0} {$i < 10} {incr i} {
        set arr($i) $i
    }

    # array accress
    for {set i 0} {$i < 10} {incr i} {
        puts "arr($i) = $arr($i)"
    }
}

proc test_multi_dimensional_array {} {
    puts "test_multi_dimensional_array: --------------------------------"
    # init array
    for {set i 0} {$i < 3} {incr i} {
        for {set j 0} {$j < 3} {incr j} {
            # multi dim: arr(i,j,k,l,...)
            set arr($i,$j) [expr $i + $j]
        }
    }

    # array accress
    for {set i 0} {$i < 3} {incr i} {
        for {set j 0} {$j < 3} {incr j} {
            puts -nonewline "$arr($i,$j) "
        }
        puts ""
    }
}

proc main {} {
    test_array
    test_multi_dimensional_array
}

main
