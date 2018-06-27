cmake_minimum_required(VERSION 3.9)
project(Dec++isionTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -W -Weffc++")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(include test/include)

set(FILES
        src/DataReader.cpp
        src/DecisionTree.cpp
        src/Question.cpp
        src/Leaf.cpp
        src/Node.cpp
        include/Helper.hpp
        src/Calculations.cpp
        src/TreeTest.cpp src/GraphGenerator.cpp include/GraphGenerator.hpp)

set(TEST_FILES
        test/src/Tests.cpp
        test/src/RunTest.cpp
        ${FILES})

add_executable(${PROJECT_NAME} test/main.cpp ${FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Threads::Threads)

add_executable(${PROJECT_NAME}_TEST ${TEST_FILES})
target_link_libraries(${PROJECT_NAME}_TEST ${Boost_LIBRARIES} Threads::Threads)