cmake_minimum_required(VERSION 3.20.2)

project(alias_exec)

set(target_name alias_exec_v2)

add_executable(${target_name}
    main.c
)

add_custom_target(alias_exec ALL
    DEPENDS alias_exec_v2
)
