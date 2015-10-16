# required minimum version of cmake
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

option(USE_STATIC_BOOST "Statically link Boost" ${WIN32})

# set the path to the additional cmake modules
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../cmake/modules)

# set path to externals
set(CMAKE_INCLUDE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../externals/include)
set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../externals/lib)

# set report and documentation output paths
set(REPORT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../reports CACHE PATH "Reports directory")
set(COVERAGE_REPORT_DIR ${REPORT_DIR}/coverage CACHE PATH "Coverage reports output directory" )
set(TESTS_REPORT_DIR ${REPORT_DIR}/tests CACHE PATH "Testresult output directory" )

# create report and documentation output directories
file(MAKE_DIRECTORY
        ${REPORT_DIR}
        ${COVERAGE_REPORT_DIR}
        ${TESTS_REPORT_DIR}
)

set(DOC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../doc CACHE PATH "Documentation directory")

file(MAKE_DIRECTORY
        ${DOC_DIR}
)


# Check for clang compiler
if(CMAKE_CXX_COMPILER MATCHES ".*clang")
  set(CMAKE_COMPILER_IS_CLANGCXX 1)
endif()

############################################
# Create a single feature test executable. #
# Without coverage measurement             #
############################################

#
# cucumber-cpp
#
find_package(Cuke REQUIRED)

function(register_feature_steps STEP_DEFINITION_FILE)
  get_filename_component(STEP_DEFINITION_FILE_NAME ${STEP_DEFINITION_FILE} NAME)
  message(STATUS "Adding " ${STEP_DEFINITION_FILE})
  # In order to generate step definitions from multiple source files
  # we need to use set CUKE_OBJECT_PREFIX variable for every
  # source file to compile
  # https://github.com/cucumber/cucumber-cpp/issues/36
  string(REPLACE "-" "" OBJ_PREFIX ${STEP_DEFINITION_FILE_NAME})
  set_source_files_properties(${STEP_DEFINITION_FILE}.cpp PROPERTIES COMPILE_FLAGS "-DCUKE_OBJECT_PREFIX=Obj${OBJ_PREFIX}")
  set(STEP_SOURCES ${STEP_SOURCES} ${STEP_DEFINITION_FILE}.cpp PARENT_SCOPE)
endfunction()

if(CUKE_FOUND)
  register_feature_steps(features/step_definitions/step_definitions)
endif(CUKE_FOUND)

#
# Boost
#
set(CORE_BOOST_LIBS thread system regex date_time)

if(STEP_SOURCES)
  # Find all feature files
  FILE(GLOB_RECURSE FEATURE_FILES features *.feature)

  source_group("Feature Files" FILES ${FEATURE_FILES})

  add_executable(features
          ${STEP_SOURCES}
          ${FEATURE_FILES}
  )

  add_executable(tests::features ALIAS features)

  #
  # Boost
  #
  if(USE_STATIC_BOOST)
    set(Boost_USE_STATIC_LIBS ON)
  else(USE_STATIC_BOOST)
    target_compile_definitions(features
            PRIVATE
            BOOST_ALL_DYN_LINK
    )
  endif(USE_STATIC_BOOST)

  set(CORE_BOOST_LIBS thread system regex date_time chrono)

  find_package(Boost COMPONENTS  ${CORE_BOOST_LIBS} REQUIRED)

  target_link_libraries(features
          ${CUKE_LIBRARIES}
          ${Boost_LIBRARIES}
  )

  target_compile_features(features
        PUBLIC
#   cxx_aggregate_default_initializers
#   cxx_alias_templates
#   cxx_alignas
#   cxx_alignof
#   cxx_attributes
#   cxx_attribute_deprecated
        cxx_auto_type
#   cxx_binary_literals
#   cxx_constexpr
#   cxx_contextual_conversions
#   cxx_decltype_incomplete_return_types
#   cxx_decltype
#   cxx_decltype_auto
#   cxx_default_function_template_args
        cxx_defaulted_functions
        cxx_defaulted_move_initializers
        cxx_delegating_constructors
        cxx_deleted_functions
#   cxx_digit_separators
#   cxx_enum_forward_declarations
#   cxx_explicit_conversions
#   cxx_extended_friend_declarations
#   cxx_extern_templates
        cxx_final
#   cxx_func_identifier
#   cxx_generalized_initializers
#   cxx_generic_lambdas
#   cxx_inheriting_constructors
#   cxx_inline_namespaces
        cxx_lambdas
#   cxx_lambda_init_captures
#   cxx_local_type_template_args
#   cxx_long_long_type
#   cxx_noexcept
#   cxx_nonstatic_member_init
        cxx_nullptr
        cxx_override
        cxx_range_for
#   cxx_raw_string_literals
#   cxx_reference_qualified_functions
#   cxx_relaxed_constexpr
#   cxx_return_type_deduction
#   cxx_right_angle_brackets
        cxx_rvalue_references
#   cxx_sizeof_member
        cxx_static_assert
        cxx_strong_enums
#   cxx_thread_local
#   cxx_trailing_return_types
#   cxx_unicode_literals
#   cxx_uniform_initialization
#   cxx_unrestricted_unions
#   cxx_user_literals
#   cxx_variable_templates
#   cxx_variadic_macros
#   cxx_variadic_templates
#   cxx_template_template_parameters
  )
  
  if(CMAKE_COMPILER_IS_CLANGCXX)
    target_compile_options(features
            PRIVATE
            -Wno-non-virtual-dtor
            -Wno-global-constructors
    )
  endif(CMAKE_COMPILER_IS_CLANGCXX)
  
  #
  # Google Test driver
  #
  find_package(GTest REQUIRED)

  if(GTEST_FOUND)
    target_include_directories(features
            SYSTEM
            PRIVATE
            ${GTEST_INCLUDE_DIRS}
    )
    target_link_libraries(features
            ${GTEST_LIBRARIES}
    )

    if(UNIX)
      find_package(Threads) # GTest needs this and it's a static library
      target_link_libraries(features
          ${CMAKE_THREAD_LIBS_INIT}
      )
    endif(UNIX)
  endif(GTEST_FOUND)

  #
  # For using Googe Mock
  #
  find_package(GMock)

  
  if(GMOCK_FOUND)
    target_include_directories(features
            SYSTEM
            PRIVATE
            ${GMOCK_INCLUDE_DIRS}
    )
    target_link_libraries(features
            ${GMOCK_LIBRARIES}
    )
  endif(GMOCK_FOUND)

  if(WIN32)
    target_link_libraries(features
            ws2_32
    )
  endif(WIN32)
  
  if(WIN32)
    if(MSVC)
      set(FEATURE_TEST_EXE_CMD start /B ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/features.exe)
    else(MSVC)
      set(FEATURE_TEST_EXE_CMD start /B ${CMAKE_CURRENT_BINARY_DIR}/features.exe)
    endif(MSVC)
  else(WIN32)
    set(FEATURE_TEST_EXE_CMD ${CMAKE_CURRENT_BINARY_DIR}/features &)
  endif(WIN32)

  find_program(BUNDLE bundle)
  if(BUNDLE)
    message(STATUS "Installing gem dependencies")
    execute_process(COMMAND ${BUNDLE} WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
  else(BUNDLE)
    message(WARNING "Could not find Bundler: skipping Ruby Gem management")
  endif(BUNDLE)
  
  find_program(CUCUMBER_RUBY cucumber)
  if(CUCUMBER_RUBY)
    message(STATUS "Found Cucumber")
    # run feature tests target
    add_custom_target(run_feature_test
    # Run tests
            ${FEATURE_TEST_EXE_CMD}
            COMMAND cucumber -P --tags ~@wip --tags ~@proposal --no-color -f pretty -s features
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Running cucumber."
    )

    add_dependencies(run_feature_test
            tests::features
    )

    # run wip features target
    add_custom_target(run_wip_features
    # Run tests
            ${FEATURE_TEST_EXE_CMD}
            COMMAND cucumber -P --tags @wip --wip --tags ~@proposal --no-color -f pretty -s features
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Running cucumber (wip features)."
    )

    add_dependencies(run_wip_features
            features
    )

    # run wip features target
    add_custom_target(document_features
    # Run tests
            ${FEATURE_TEST_EXE_CMD}
            COMMAND cucumber -P --tags ~@wip --tags ~@proposal --no-color -f pretty --no-source -f html -o ${DOC_DIR}/Features.html features
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Running cucumber (features documentation)."
    )

    add_dependencies(document_features
            features
    )
  else(CUCUMBER_RUBY)
      message(WARNING "Could not find Cucumber: Install cucumber first in order to run tests")
  endif(CUCUMBER_RUBY)    

  #############################################
  # Create and run a feature test executable. #
  # With coverage measurement                 #
  #############################################
  if(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
    include(CodeCoverage)

    add_executable(features-cov
            EXCLUDE_FROM_ALL
            ${STEP_SOURCES}
    )

    target_link_libraries(features-cov
            ${CUKE_LIBRARIES}
            ${Boost_LIBRARIES}
            ${CMAKE_THREAD_LIBS_INIT}
    )

    if(CMAKE_COMPILER_IS_CLANGCXX)
      target_compile_options(features-cov
              PRIVATE
              -Wno-non-virtual-dtor
              -Wno-global-constructors
      )
    endif(CMAKE_COMPILER_IS_CLANGCXX)

    if(GTEST_FOUND)
      target_include_directories(features-cov
              SYSTEM
              PRIVATE
              ${GTEST_INCLUDE_DIRS}
      )
      target_link_libraries(features-cov
              ${GTEST_LIBRARIES}
      )
    endif(GTEST_FOUND)

    if(GMOCK_FOUND)
      target_include_directories(features-cov
              SYSTEM
              PRIVATE
              ${GMOCK_INCLUDE_DIRS}
      )
      target_link_libraries(features-cov
              ${GMOCK_LIBRARIES}
      )
    endif(GMOCK_FOUND)

    setup_target_under_cucumber_for_coverage_cobertura(
            coverage_features
            features-cov
            ${COVERAGE_REPORT_DIR}/features
            ${PROJECT_SOURCE_DIR}/tests/feature/features
            ""
    )
  endif(UNIX AND CMAKE_COMPILER_IS_GNUCXX AND CMAKE_BUILD_TYPE MATCHES Debug)
endif(STEP_SOURCES)
