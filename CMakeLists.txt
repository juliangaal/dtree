cmake_minimum_required(VERSION 3.9)
project(dtree VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

option(COMPILE_TEST "Compiles Tests" OFF)
option(PY_BINDINGS "Enable Python bindings generation" OFF)

message(STATUS "CMake Version ${CMAKE_VERSION}")
message(STATUS "Build Type ${CMAKE_BUILD_TYPE}")

find_package(Boost REQUIRED)
find_package(OpenMP REQUIRED)
find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)

# for future clang support, clang seems to not like openmp
set(CLANG_DEFAULT_CXX_STDLIB "libc++")

set(SOURCES src/calculations.cxx
            src/data_reader.cxx
            src/validation.cxx
            src/question.cxx
            src/node.cxx
            src/generate.cxx
            src/decision_tree.cxx)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${Boost_INCLUDE_DIRS}
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX fmt::fmt stdc++fs) # stdc++fs for g++-8
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Weffc++ -Wpedantic)

enable_testing()

add_executable(dtree_test test/tests.cxx ${HEADERS})
add_test(NAME dtree_test COMMAND dtree_test)
target_include_directories(dtree_test PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_options(dtree_test PRIVATE -Wall -Weffc++ -Wpedantic)
target_link_libraries(dtree_test dtree fmt::fmt stdc++fs Catch2::Catch2)

add_executable(quick_tester test/quick_tester.cxx)
target_compile_options(quick_tester PRIVATE -Wall -Weffc++ -Wpedantic)
target_include_directories(quick_tester PUBLIC ../include ${Boost_INCLUDE_DIRS})
target_link_libraries(quick_tester OpenMP::OpenMP_CXX dtree fmt::fmt)

# pybind11
message(STATUS "PY_BINDINGS set to ${PY_BINDINGS}")
if(PY_BINDINGS)
    find_package(pybind11 REQUIRED)
    pybind11_add_module(dtree_py src/bindings.cxx)
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang") # additional clang fixes needed, see https://github.com/pybind/pybind11/issues/1604
        message(FATAL_ERROR "Python bindings are currently only supported with g++")
    endif()
    target_include_directories(dtree_py PRIVATE include)
    target_link_libraries(dtree_py PRIVATE dtree)
    set_target_properties(dtree_py
                          PROPERTIES
                          LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts)
endif()

# generate docs
add_custom_target(doc)
add_custom_command(TARGET doc
                   COMMAND cd ${PROJECT_SOURCE_DIR}/docs && doxygen Doxyfile)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES ${HEADERS} DESTINATION ../include/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
                                 VERSION ${${PROJECT_NAME}_VERSION}
                                 COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})