cmake_minimum_required(VERSION 3.13)

include(${CMAKE_CURRENT_LIST_DIR}/at_commands_lib_include.cmake)

project(at-commands-example)

set(CMAKE_C_STANDARD 11)

add_executable(${PROJECT_NAME} example.c)

target_link_libraries(${PROJECT_NAME} 
    at-commands
)
