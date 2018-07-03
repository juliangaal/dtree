cmake_minimum_required(VERSION 3.1)
project(Test)

set(CMAKE_CXX_STANDARD 17)

find_package(DecisionTree REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_executable(Test import_test.cpp)
target_link_libraries(Test DecisionTree Threads::Threads ${Boost_LIBRARIES})