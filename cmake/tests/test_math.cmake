# learning cmake math
# run: cmake -P test_math.cmake
# 2023.05.16

function(test_numeric)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # add
    message("add: ----------")
    math(EXPR num "1 + 2")
    message("1 + 2 = ${num}")
    math(EXPR num "1 + (-3)")
    message("1 + (-3) = ${num}")
    math(EXPR num "-3 + 3")
    message("-3 + 3 = ${num}")

    # sub
    message("sub: ----------")
    math(EXPR num "5 - 2")
    message("5 - 2 = ${num}")
    math(EXPR num "1 - (-3)")
    message("1 - (-3) = ${num}")
    math(EXPR num "-3 - 1")
    message("-3 - 1 = ${num}")

    # mul
    message("mul: ----------")
    math(EXPR num "5 * 2")
    message("5 * 2 = ${num}")
    math(EXPR num "2 * (-3)")
    message("2 * (-3) = ${num}")
    math(EXPR num "0 * 4")
    message("0 * 4 = ${num}")

    # div
    message("div: ----------")
    math(EXPR num "5 / 2")
    message("5 / 2 = ${num}")
    math(EXPR num "2 / (-3)")
    message("2 / (-3) = ${num}")
    math(EXPR num "10 / 4")
    message("10 / 4 = ${num}")

    # mod
    message("mod: ----------")
    math(EXPR num "5 % 2")
    message("5 % 2 = ${num}")
    math(EXPR num "3 % (-2)")
    message("3 % (-2) = ${num}")
    math(EXPR num "-10 % 4")
    message("-10 % 4 = ${num}")
endfunction()

function(test_bit)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # and
    message("and: ----------")
    math(EXPR num "0xe & 0xd" OUTPUT_FORMAT HEXADECIMAL)
    message("0xe & 0xd = ${num}")

    # or
    message("or: ----------")
    math(EXPR num "0xc | 0x3" OUTPUT_FORMAT HEXADECIMAL)
    message("0xc | 0x3 = ${num}")

    # not
    message("not: ----------")
    math(EXPR num "~0x0" OUTPUT_FORMAT HEXADECIMAL)
    message("~0x0 = ${num}")
    math(EXPR num "~0xf" OUTPUT_FORMAT HEXADECIMAL)
    message("~0xf = ${num}")

    # xor
    message("xor: ----------")
    math(EXPR num "0xc ^ 0x3" OUTPUT_FORMAT HEXADECIMAL)
    message("0xc ^ 0x3 = ${num}")

    # left shift
    message("left shift: ----------")
    math(EXPR num "0xff << 4" OUTPUT_FORMAT HEXADECIMAL)
    message("0xff << 4 = ${num}")

    # right shift
    message("right shift: ----------")
    math(EXPR num "0xff >> 4" OUTPUT_FORMAT HEXADECIMAL)
    message("0xff >> 4 = ${num}")
endfunction()

function(test_hex)
    message("${CMAKE_CURRENT_FUNCTION}: --------------------------------------")

    # decimal to hexadecimal
    set(dec 20)
    math(EXPR hex ${dec} OUTPUT_FORMAT HEXADECIMAL)
    message("${dec} = ${hex}")

    # hexadecimal to decimal
    set(hex 0xff)
    math(EXPR dec ${hex} OUTPUT_FORMAT DECIMAL)
    message("${hex} = ${dec}")
endfunction()

function(main)
    test_numeric()
    test_bit()
    test_hex()
endfunction()

main()
