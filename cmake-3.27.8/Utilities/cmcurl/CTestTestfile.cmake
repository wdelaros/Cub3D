# CMake generated Testfile for 
# Source directory: /Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Utilities/cmcurl
# Build directory: /Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Utilities/cmcurl
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[curl]=] "curltest" "http://open.cdash.org/user.php")
set_tests_properties([=[curl]=] PROPERTIES  _BACKTRACE_TRIPLES "/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Utilities/cmcurl/CMakeLists.txt;1580;add_test;/Users/wdelaros/Desktop/Cub3D/cmake-3.27.8/Utilities/cmcurl/CMakeLists.txt;0;")
subdirs("lib")
