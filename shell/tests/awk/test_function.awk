#!/usr/bin/awk -f
# run: ./test_print.awk file.txt

BEGIN {
    # only execute once
    main()
}

END {
}

# functions with no parameters and no return value
function test_hello() {
    print "hello awk"
}

# functions with parameters
function test_name(name, age) {
    # using parameter
    print "person name: " name ", age: " age
}

# functions with parameters and return value
function test_add(a, b) {
    sum = a + b
    return sum
}

function main() {
    # function call
    test_hello()
    # function call with parameters
    test_name("Bob", 19)
    # get function return value
    print "3 + 5 = " test_add(3, 5)
}

# For each line in the file, execute the code here
{
    #main()
}
