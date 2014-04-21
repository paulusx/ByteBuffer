cmake_minimum_required (VERSION 2.6)

project(ByteBuffera)
include (CPack)

add_definitions( -Wall -Wextra -pedantic -Wno-long-long -g  -std=c++11)

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_MULTITHREADED ON)

find_package (Boost COMPONENTS unit_test_framework REQUIRED)


include_directories(  
  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  "${Boost_INCLUDE_DIRS}"
  )

set(LIBRARIES "${Boost_LIBRARIES}")

add_subdirectory(test)

enable_testing ()
add_test(Checker "test/run-check")
