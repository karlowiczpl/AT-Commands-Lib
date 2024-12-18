set(SOURCES 
  map.c
  map.h
  parser.c
  parser.h
)

add_library(Komendy_at_lib STATIC ${SOURCES})

target_include_directories(Komendy_at_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
