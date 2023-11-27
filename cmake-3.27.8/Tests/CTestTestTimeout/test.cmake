cmake_minimum_required(VERSION 3.5)

# Settings:
set(CTEST_DASHBOARD_ROOT                "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestTest")
set(CTEST_SITE                          "c2r5p10.42quebec.com")
set(CTEST_BUILD_NAME                    "CTestTest-Darwin-clang++-Timeout")

set(CTEST_SOURCE_DIRECTORY              "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestTestTimeout")
set(CTEST_BINARY_DIRECTORY              "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestTestTimeout")
set(CTEST_CVS_COMMAND                   "")
set(CTEST_CMAKE_GENERATOR               "Unix Makefiles")
set(CTEST_CMAKE_GENERATOR_PLATFORM      "")
set(CTEST_CMAKE_GENERATOR_TOOLSET       "")
set(CTEST_BUILD_CONFIGURATION           "$ENV{CMAKE_CONFIG_TYPE}")
set(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
set(CTEST_NOTES_FILES                   "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

#CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

file(WRITE "${CTEST_BINARY_DIRECTORY}/CMakeCache.txt" "
TIMEOUT:STRING=
")

CTEST_START(Experimental)
CTEST_CONFIGURE(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_BUILD(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_TEST(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)

set(log ${CTEST_BINARY_DIRECTORY}/timeout.log)
if(EXISTS "${log}")
  # Verify that the timeout test did not finish sleeping.
  file(STRINGS "${log}" after_sleep REGEX "after sleep")
  if(after_sleep)
    message(FATAL_ERROR "Log indicates timeout did not kill child.")
  else()
    message(STATUS "Log indicates timeout correctly killed child.")
  endif()
else()
  message(FATAL_ERROR "Log does not exist:\n  ${log}")
endif()
