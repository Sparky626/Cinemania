# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Report_48_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Report_48_autogen.dir\\ParseCache.txt"
  "Report_48_autogen"
  )
endif()
