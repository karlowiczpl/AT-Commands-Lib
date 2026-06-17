cmake_minimum_required(VERSION 3.16)

set(SOURCES
  ${CMAKE_CURRENT_LIST_DIR}/src/map.c
  ${CMAKE_CURRENT_LIST_DIR}/src/parser.c
)

add_library(at-commands STATIC ${SOURCES})

target_include_directories(at-commands PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}/inc/
)
