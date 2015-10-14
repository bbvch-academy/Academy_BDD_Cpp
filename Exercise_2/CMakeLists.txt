# C++ Project template main cmake file

# required minimum version of cmake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW)

# project name
# TODO fill in your project name and version
project(BDD_with_Cpp_Exercise_2)

# Cmake cache variables
option(BUILD_EXTERNALS "Build also external libraries" TRUE)

# set default built type to Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

# Cmake test
enable_testing()

#
# Generic Compiler Flags
#

# Check for clang compiler
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGCXX 1)
endif()

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

find_package(Boost)
if(Boost_FOUND)
    add_subdirectory(src)
endif(Boost_FOUND)

# unit tests require gmock
find_package(GMock)

if(GMOCK_FOUND)
  add_subdirectory(tests/unit)
endif(GMOCK_FOUND)

# feature tests require cucumber-cpp (aka cuke)
find_package(Cuke)

if(CUKE_FOUND AND Boost_FOUND)
  add_subdirectory(tests/feature)
endif(CUKE_FOUND AND Boost_FOUND)
 
# Add some custom target
if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
  add_custom_target(coverage)
endif(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)

if(TARGET coverage_unittests)
  add_dependencies(coverage coverage_unittests)
endif(TARGET coverage_unittests)

if(TARGET coverage_features)
  add_dependencies(coverage coverage_features)
endif(TARGET coverage_features)

add_custom_target(remove_externals
  ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/externals/include
  COMMAND ${CMAKE_COMMAND} -E remove_directory ${PROJECT_SOURCE_DIR}/externals/lib
  COMMENT "Remove externals (lib & include)." VERBATIM
)

