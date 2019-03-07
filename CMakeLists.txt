##################################################################
#
# SS - Simultaneous Sort
#
# Small header-only library that implements a technique that
# allows to sort a primary array, as well as to reorder additional
# arrays simultaneously.
#
# Copyright 2019
# Alexander Straub
#
##################################################################
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

# Create project/solution
project("simultaneous_sort")

# Set default build type on non-multi-configuration platforms
get_property(IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(NOT CMAKE_BUILD_TYPE AND NOT IS_MULTI_CONFIG)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the build configuration." FORCE)

  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

# Let user select options
option(ss_option_build_test "Build test project with small sample demonstrating its usage." ON)

# Create test project
if(ss_option_build_test)
  if(MSVC)
    file(GLOB header_files LIST_DIRECTORIES FALSE "include/*.h")
  else()
    set(header_files)
  endif()

  add_executable(ss_test src/test.cpp ${header_files})

  set_target_properties(ss_test PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON)
  target_include_directories(ss_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

# Create header-only target for installation
add_library(simultaneous_sort INTERFACE)

target_include_directories(simultaneous_sort INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(TARGETS simultaneous_sort EXPORT simultaneous_sort-config)
install(DIRECTORY include/ DESTINATION include/simultaneous_sort)

install(EXPORT simultaneous_sort-config DESTINATION share/simultaneous_sort/cmake)
export(TARGETS simultaneous_sort FILE simultaneous_sort-config.cmake)