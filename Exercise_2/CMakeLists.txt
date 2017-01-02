# C++ Project template main cmake file

# required minimum version of cmake
cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW)

# project name
# TODO fill in your project name and version
project(Home_Automation_System VERSION 1.2.0 LANGUAGES CXX C)

# project name used in doxygen docu
STRING(REGEX REPLACE "_" " " PROJECT_DOC_NAME ${PROJECT_NAME})

# project name used for installation
set(APPLICATION_NAME ${PROJECT_DOC_NAME})

if (WIN32)
  # Set a install path in the project folder
  # Windows 7 can not install directly into the default folder (e.g. C:/Program Files (x86)/Cpp_Project_Template)
  set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/install CACHE PATH "Install path prefix" FORCE)
endif (WIN32)


# Cmake cache variables
option(BUILD_EXTERNALS "Build also external libraries" TRUE)

set(EXT_INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/externals)
set(EXT_INSTALL_INCLUDE_DIR ${EXT_INSTALL_DIR}/include)
set(EXT_INSTALL_LIB_DIR ${EXT_INSTALL_DIR}/lib)

set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

file(MAKE_DIRECTORY
    ${EXT_INSTALL_DIR}
    ${EXT_INSTALL_INCLUDE_DIR}
    ${EXT_INSTALL_LIB_DIR}
    ${RUNTIME_OUTPUT_DIRECTORY}
    )

set(CMAKE_INCLUDE_PATH ${EXT_INSTALL_INCLUDE_DIR})
set(CMAKE_LIBRARY_PATH ${EXT_INSTALL_LIB_DIR})

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
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Xlinker '--no-as-needed'")
endif(UNIX)

# set the path to the additional cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules)

# external libraries
if(BUILD_EXTERNALS)
  add_subdirectory(externals)
endif(BUILD_EXTERNALS)


add_subdirectory(src)

# unit tests require gmock
find_package(GMock)

if(GMOCK_FOUND)
  add_subdirectory(tests/unit)
endif(GMOCK_FOUND)

# feature tests require cucumber-cpp (aka cuke)
find_package(Cuke)

if(CUKE_FOUND)
  add_subdirectory(tests/feature)
endif(CUKE_FOUND)
