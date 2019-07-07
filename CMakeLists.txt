cmake_minimum_required(VERSION 3.9)
project(DecisionTree VERSION 0.2)

set(CMAKE_CXX_STANDARD 17)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(Boost REQUIRED)
find_package(OpenMP REQUIRED)
find_package(fmt REQUIRED)

# for future clang support, clang seems to not like openmp
# set(CLANG_DEFAULT_CXX_STDLIB "libc++")

AUX_SOURCE_DIRECTORY(src SOURCES)
AUX_SOURCE_DIRECTORY(include HEADERS)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC
                           ${Boost_INCLUDE_DIRS}
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX fmt::fmt)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Weffc++ -Wpedantic)

enable_testing()

add_executable(dtree_test test/src/tests.cpp ${HEADERS})
add_test(NAME dtree_test COMMAND dtree_test)
target_include_directories(dtree_test PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_options(dtree_test PRIVATE -Wall -Weffc++ -Wpedantic)
target_link_libraries(dtree_test DecisionTree fmt::fmt)

add_executable(quick_tester test/src/quick_tester.cpp)
target_compile_options(quick_tester PRIVATE -Wall -Weffc++ -Wpedantic)
target_include_directories(quick_tester PUBLIC ../include ${Boost_INCLUDE_DIRS})
target_link_libraries(quick_tester OpenMP::OpenMP_CXX DecisionTree fmt::fmt)

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