# save return value in parameter
function(add a b sum)
    math(EXPR num "${a} + ${b}")
    set(${sum} ${num} PARENT_SCOPE)
endfunction()
