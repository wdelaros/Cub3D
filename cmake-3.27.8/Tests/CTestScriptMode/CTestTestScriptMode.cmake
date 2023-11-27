# This script will be executed with ctest -S

# Check that the system name is determined correctly:
set(CMAKE_CMAKE_SYSTEM_NAME "Darwin")

if (NOT "${CMAKE_SYSTEM_NAME}" STREQUAL "${CMAKE_CMAKE_SYSTEM_NAME}")
   message(FATAL_ERROR "Error: CMAKE_SYSTEM_NAME is \"${CMAKE_SYSTEM_NAME}\", but should be \"Darwin\"")
endif()

# this seems to be necessary, otherwise ctest complains that these
# variables are not set:
set(CTEST_COMMAND "\"/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/bin/ctest\"")
set(CTEST_SOURCE_DIRECTORY "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestScriptMode/")
set(CTEST_BINARY_DIRECTORY "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestScriptMode/")
