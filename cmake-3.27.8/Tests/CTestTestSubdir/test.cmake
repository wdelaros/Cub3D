cmake_minimum_required(VERSION 3.5)

# Settings:
set(CTEST_DASHBOARD_ROOT                "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestTest")
set(CTEST_SITE                          "c2r5p10.42quebec.com")
set(CTEST_BUILD_NAME                    "CTestTest-Darwin-clang++-Subdir")

set(CTEST_SOURCE_DIRECTORY              "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestTestSubdir")
set(CTEST_BINARY_DIRECTORY              "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Tests/CTestTestSubdir")
set(CTEST_CVS_COMMAND                   "")
set(CTEST_CMAKE_GENERATOR               "Unix Makefiles")
set(CTEST_CMAKE_GENERATOR_PLATFORM      "")
set(CTEST_CMAKE_GENERATOR_TOOLSET       "")
set(CTEST_BUILD_CONFIGURATION           "$ENV{CMAKE_CONFIG_TYPE}")
set(CTEST_COVERAGE_COMMAND              "/usr/bin/gcov")
set(CTEST_NOTES_FILES                   "${CTEST_SCRIPT_DIRECTORY}/${CTEST_SCRIPT_NAME}")

#CTEST_EMPTY_BINARY_DIRECTORY(${CTEST_BINARY_DIRECTORY})

CTEST_START(Experimental)
CTEST_CONFIGURE(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_BUILD(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
CTEST_TEST(BUILD "${CTEST_BINARY_DIRECTORY}" RETURN_VALUE res)
