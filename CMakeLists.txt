cmake_minimum_required(VERSION 3.20)

project(libotocurl VERSION 0.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)
option(BUILD_UNIT_TESTS "Build unit tests" OFF)
option(BUILD_INTEGRATION_TESTS "Build integration tests" OFF)

# Use double quotes to account for case when CMAKE_BUILD_TYPE is empty.
string(TOUPPER "${CMAKE_BUILD_TYPE}" CMAKE_BUILD_TYPE)

if(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
    add_compile_definitions(DEBUG_BUILD=1)
endif()

add_subdirectory(libotocurl)

if(BUILD_UNIT_TESTS OR BUILD_INTEGRATION_TESTS)
    enable_testing()
endif()