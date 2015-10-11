# required minimum version of cmake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

# project name
# TODO fill in your project name and version
project(BDD_with_Cpp_Exercise_1)


# Cmake cache variables
option(BUILD_EXTERNALS "Build also external libraries" TRUE)

# set default built type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# Check for clang compiler
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGCXX 1)
endif()

#
# Generic Compiler Flags
#

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(UNIX)

# set the path to the additional cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# set path to externals
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/externals/include)
set(CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/externals/lib)

# external libraries
if(BUILD_EXTERNALS)
  add_subdirectory(externals)
endif(BUILD_EXTERNALS)


# feature tests require cucumber-cpp (aka cuke)
find_package(Cuke)
find_package(GTest)
if(CUKE_FOUND)
  add_subdirectory(tests/feature)
endif(CUKE_FOUND)

  
# Add some custom target
if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
  add_custom_target(coverage)
endif(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)

if(TARGET coverage_features)
  add_dependencies(coverage coverage_features)
endif(TARGET coverage_features)

