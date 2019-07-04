cmake_minimum_required(VERSION 3.1)
project(Test)

set(CMAKE_CXX_STANDARD 17)

find_package(DecisionTree 0.1 REQUIRED)
if(DecisionTree_FOUND)
    message("-- DecisionTree version: ${DecisionTree_VERSION}")
endif()

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
find_package(OpenMP 5.0 REQUIRED)

set (FILES
        ../lib/src/DataReader.cpp
        ../lib/src/DecisionTree.cpp
        ../lib/src/Question.cpp
        ../lib/src/Leaf.cpp
        ../lib/src/Node.cpp
        ../lib/src/Calculations.cpp
        ../lib/src/TreeTest.cpp
        ../lib/src/GraphGenerator.cpp
        ../lib/src/GraphElements.cpp)

add_executable(ImportTest import_test.cpp)
target_include_directories(ImportTest PUBLIC ../lib/include ${Boost_INCLUDE_DIRS})
target_compile_options(ImportTest PRIVATE -Wall -Weffc++ -Wpedantic)
target_link_libraries(ImportTest DecisionTree Threads::Threads ${Boost_LIBRARIES})

add_executable(Test src/RunTest.cpp src/Tests.cpp)
target_include_directories(Test PUBLIC ../lib/include ${Boost_INCLUDE_DIRS})
target_compile_options(Test PRIVATE -Wall -Weffc++ -Wpedantic)
target_link_libraries(Test DecisionTree Threads::Threads ${Boost_LIBRARIES})

add_executable(RandomTest random_tester.cpp ${FILES})
target_compile_options(RandomTest PRIVATE -Wall -Weffc++ -Wpedantic)
target_include_directories(RandomTest PUBLIC ../lib/include ${Boost_INCLUDE_DIRS})
target_link_libraries(RandomTest Threads::Threads ${Boost_LIBRARIES} OpenMP::OpenMP_CXX)