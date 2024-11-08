# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/VSMT_Host_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/VSMT_Host_autogen.dir/ParseCache.txt"
  "VSMT_Host_autogen"
  )
endif()
