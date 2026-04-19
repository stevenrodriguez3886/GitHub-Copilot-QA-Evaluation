cmake_minimum_required(VERSION 3.14)
project(Copilot_Boost_Coverage_Eval)

# Enable CTest framework
enable_testing()

# Find local Boost installation
find_package(Boost REQUIRED COMPONENTS unit_test_framework)

# Inject Code Coverage Flags for GCC/Clang
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Fetch Google Test automatically (Official Release v1.15.2)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ==========================================
# Case 1: Trim
# ==========================================
add_executable(case1_copilot_tests tests/case1_trim/copilot_trim_test.cpp)
target_link_libraries(case1_copilot_tests gtest_main Boost::headers)
include(GoogleTest)
gtest_discover_tests(case1_copilot_tests)

# Boost Baseline Target
add_executable(case1_boost_baseline tests/case1_trim/boost_trim_test.cpp)
target_link_libraries(case1_boost_baseline Boost::unit_test_framework)
add_test(NAME case1_boost COMMAND case1_boost_baseline)

# ==========================================
# Case 2: Replace All
# ==========================================
add_executable(case2_copilot_tests tests/case2_replace/copilot_replace_test.cpp)
target_link_libraries(case2_copilot_tests gtest_main Boost::headers)
gtest_discover_tests(case2_copilot_tests)

# Boost Baseline Target
add_executable(case2_boost_baseline tests/case2_replace/boost_replace_test.cpp)
target_link_libraries(case2_boost_baseline Boost::unit_test_framework)
add_test(NAME case2_boost COMMAND case2_boost_baseline)

# ==========================================
# Case 3: Split
# ==========================================
add_executable(case3_copilot_tests tests/case3_split/copilot_split_test.cpp)
target_link_libraries(case3_copilot_tests gtest_main Boost::headers)
gtest_discover_tests(case3_copilot_tests)

# Boost Baseline Target
add_executable(case3_boost_baseline tests/case3_split/boost_split_test.cpp)
target_link_libraries(case3_boost_baseline Boost::unit_test_framework)
add_test(NAME case3_boost COMMAND case3_boost_baseline)