-- learning lua function
-- run: lua test_function.lua
-- 2023.05.17

-- global function, no parameter, no return value
function test_print()
    print(debug.getinfo(1).name, ": ---------------------------------")
    print("hello lua")
end

function main()
    test_print()
end

main()
