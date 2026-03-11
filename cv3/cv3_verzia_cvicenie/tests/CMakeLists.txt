cmake_minimum_required(VERSION 3.14)
project(UnitTestsFifo)

cmake_minimum_required(VERSION 3.14)
project(UnitTestsFifo)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(testik tests.cpp)

# Tu povieš, že tvoj program potrebuje GoogleTest a tvoju knižnicu fifo_lib
target_link_libraries(testik
        PRIVATE
        GTest::gtest
        GTest::gtest_main
        fifo_lib           # Názov tvojej knižnice zo zadania
)

# Príkaz, aby CMake vedel, že ide o testy
include(GoogleTest)
gtest_discover_tests(testik)
