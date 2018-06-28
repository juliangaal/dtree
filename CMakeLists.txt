cmake_minimum_required(VERSION 3.9)
project(Dec++isionTree)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -W -Weffc++")

find_package(Boost REQUIRED)
find_package(Threads REQUIRED)

include_directories(${Boost_INCLUDE_DIR})
include_directories(include)

set(FILES
        src/DataReader.cpp
        src/DecisionTree.cpp
        src/Question.cpp
        src/Leaf.cpp
        src/Node.cpp
        include/Helper.hpp
        src/Calculations.cpp
        src/TreeTest.cpp src/GraphGenerator.cpp)

add_executable(${PROJECT_NAME} test/main.cpp ${FILES})
target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} Threads::Threads)