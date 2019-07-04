add_executable(test src/tests.cpp ${HEADERS})
target_include_directories(test PRIVATE ${Boost_INCLUDE_DIRS})
target_compile_options(test PRIVATE -Wall -Weffc++ -Wpedantic)
target_link_libraries(test DecisionTree)

add_executable(quick_tester src/quick_tester.cpp)
target_compile_options(quick_tester PRIVATE -Wall -Weffc++ -Wpedantic)
target_include_directories(quick_tester PUBLIC ../include ${Boost_INCLUDE_DIRS})
target_link_libraries(quick_tester OpenMP::OpenMP_CXX DecisionTree)