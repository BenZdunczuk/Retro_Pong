# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\pong_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\pong_autogen.dir\\ParseCache.txt"
  "pong_autogen"
  )
endif()
