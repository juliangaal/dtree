cmake_minimum_required(VERSION 3.1)
project(Test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g -W -Weffc++ -Werror")

find_package(DecisionTree REQUIRED)
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_executable(ImportTest import_test.cpp)
target_link_libraries(ImportTest DecisionTree Threads::Threads ${Boost_LIBRARIES})

add_executable(Test src/RunTest.cpp src/Tests.cpp)
target_link_libraries(Test DecisionTree Threads::Threads ${Boost_LIBRARIES})