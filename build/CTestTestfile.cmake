# CMake generated Testfile for 
# Source directory: /home/stevenrodriguez3886/copilot_evaluation
# Build directory: /home/stevenrodriguez3886/copilot_evaluation/build
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
include("/home/stevenrodriguez3886/copilot_evaluation/build/case1_copilot_tests[1]_include.cmake")
add_test(case1_boost "/home/stevenrodriguez3886/copilot_evaluation/build/case1_boost_baseline")
set_tests_properties(case1_boost PROPERTIES  _BACKTRACE_TRIPLES "/home/stevenrodriguez3886/copilot_evaluation/CMakeLists.txt;35;add_test;/home/stevenrodriguez3886/copilot_evaluation/CMakeLists.txt;0;")
add_test(case2_boost "/home/stevenrodriguez3886/copilot_evaluation/build/case2_boost_baseline")
set_tests_properties(case2_boost PROPERTIES  _BACKTRACE_TRIPLES "/home/stevenrodriguez3886/copilot_evaluation/CMakeLists.txt;48;add_test;/home/stevenrodriguez3886/copilot_evaluation/CMakeLists.txt;0;")
add_test(case3_boost "/home/stevenrodriguez3886/copilot_evaluation/build/case3_boost_baseline")
set_tests_properties(case3_boost PROPERTIES  _BACKTRACE_TRIPLES "/home/stevenrodriguez3886/copilot_evaluation/CMakeLists.txt;61;add_test;/home/stevenrodriguez3886/copilot_evaluation/CMakeLists.txt;0;")
subdirs("_deps/googletest-build")
