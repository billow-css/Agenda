# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\appAgenda_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\appAgenda_autogen.dir\\ParseCache.txt"
  "appAgenda_autogen"
  )
endif()
