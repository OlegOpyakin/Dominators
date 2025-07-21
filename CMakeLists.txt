cmake_minimum_required(VERSION 3.6)
project(Dominators)

set(CMAKE_CXX_FLAGS "-std=c++20 -g -O2")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++20 -Wall -g -O0 -fsanitize=address -fsanitize=undefined")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Dominator src/main.cc)
add_executable(TESTS src/TESTS.cc)

target_include_directories(Dominator PUBLIC inc/)
target_include_directories(TESTS PUBLIC inc/)

target_link_libraries(TESTS GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(TESTS)