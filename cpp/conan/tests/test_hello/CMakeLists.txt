cmake_minimum_required(VERSION 3.15)
project(hello CXX)



add_executable(hello src/hello.cpp src/main.cpp)



install(TARGETS hello DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
