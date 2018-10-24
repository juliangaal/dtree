find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

set(CLANG_DEFAULT_CXX_STDLIB "libc++")

set(SOURCES
        src/DataReader.cpp
        src/DecisionTree.cpp
        src/Question.cpp
        src/Leaf.cpp
        src/Node.cpp
        src/Calculations.cpp
        src/TreeTest.cpp
        src/GraphGenerator.cpp
        src/GraphElements.cpp)

set(HEADERS
        include/Dataset.hpp
        include/DataReader.hpp
        include/DecisionTree.hpp
        include/Question.hpp
        include/Leaf.hpp
        include/Node.hpp
        include/Helper.hpp
        include/Calculations.hpp
        include/TreeTest.hpp
        include/GraphGenerator.hpp
        include/GraphElements.hpp)

add_library(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Threads::Threads)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Weffc++ -Wpedantic)
target_include_directories(${PROJECT_NAME} PUBLIC
        ${Boost_INCLUDE_DIR}
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

install(TARGETS ${PROJECT_NAME}
        EXPORT ${PROJECT_NAME}Targets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin)

install(EXPORT ${PROJECT_NAME}Targets
        FILE ${PROJECT_NAME}Config.cmake
        DESTINATION lib/cmake/${PROJECT_NAME})

install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
        VERSION ${${PROJECT_NAME}_VERSION}
        COMPATIBILITY SameMajorVersion)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
        DESTINATION lib/cmake/${PROJECT_NAME})