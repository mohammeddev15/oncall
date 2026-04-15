# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\_Oncall__autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\_Oncall__autogen.dir\\ParseCache.txt"
  "_Oncall__autogen"
  )
endif()
