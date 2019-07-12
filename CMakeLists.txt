cmake_minimum_required(VERSION 3.9)
project(dtree VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(PY_LIB dtree_py)
option(COMPILE_TEST "Compiles Tests" OFF)
option(PY_BINDINGS "Enable Pyhton bindings generation" OFF)

message(STATUS "Build Type ${CMAKE_BUILD_TYPE}")

find_package(Boost REQUIRED)
find_package(OpenMP REQUIRED)
find_package(fmt REQUIRED)

# for future clang support, clang seems to not like openmp
set(CLANG_DEFAULT_CXX_STDLIB "libc++")

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(include HEADERS)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${Boost_INCLUDE_DIRS}
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX fmt::fmt stdc++fs) # stdc++fs for g++-8
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Weffc++ -Wpedantic)

enable_testing()

add_executable(dtree_test test/src/tests.cpp ${HEADERS})
add_test(NAME dtree_test COMMAND dtree_test)
target_include_directories(dtree_test PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_options(dtree_test PRIVATE -Wall -Weffc++ -Wpedantic)
target_link_libraries(dtree_test dtree fmt::fmt stdc++fs)

add_executable(quick_tester test/src/quick_tester.cpp)
target_compile_options(quick_tester PRIVATE -Wall -Weffc++ -Wpedantic)
target_include_directories(quick_tester PUBLIC ../include ${Boost_INCLUDE_DIRS})
target_link_libraries(quick_tester OpenMP::OpenMP_CXX dtree fmt::fmt)

message(STATUS "PY_BINDINGS set to ${PY_BINDINGS}")
if(PY_BINDINGS)
    # Update submodules as needed
    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/pybind11")
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()

    if(NOT EXISTS "${CMAKE_SOURCE_DIR}/pybind11/CMakeLists.txt")
        message(FATAL_ERROR "The submodules were not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again.")
    endif()

    # pybind11 bindings
    add_subdirectory(pybind11)
    pybind11_add_module(${PY_LIB} src/bindings.cxx)
#    target_link_libraries(${PY_LIB} PRIVATE ${LIB})
    set_target_properties(${PY_LIB}
                          PROPERTIES
                          LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/scripts)
endif()

# enable tests compilation when COMPILE_TEST=ON
#message(STATUS "COMPILE_TEST set to ${COMPILE_TEST}")
#if(COMPILE_TEST)
#    find_package(Catch2 REQUIRED)
#    enable_testing()
#
#    add_executable(unit_test tests/test.cpp)
#    add_test(NAME unit_test COMMAND unit_test)
#    target_include_directories(unit_test PRIVATE include)
#    target_compile_options(unit_test PRIVATE -Wall -Wextra -pedantic -Werror)
#    target_link_libraries(unit_test PRIVATE
#                          ${OpenCV_LIBS}
#                          Catch2::Catch2
#                          notqrcode)
#
#    add_executable(main src/main.cpp)
#    target_include_directories(main PRIVATE include)
#    target_compile_options(main PRIVATE -Wall -Wextra -Weffc++ -pedantic -Werror)
#    target_link_libraries(main PRIVATE
#                          ${OpenCV_LIBS}
#                          fmt::fmt
#                          notqrcode)
#endif()

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