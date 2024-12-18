set(SOURCES 
  map.c
  map.h
  parser.c
  parser.h
)

add_library(AT_commands_lib STATIC ${SOURCES})

target_include_directories(AT_commands_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
