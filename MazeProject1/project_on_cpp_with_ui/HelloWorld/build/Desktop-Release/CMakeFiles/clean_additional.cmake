# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles/HelloWorld_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/HelloWorld_autogen.dir/ParseCache.txt"
  "HelloWorld_autogen"
  )
endif()