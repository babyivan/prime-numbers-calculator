cmake_minimum_required(VERSION 3.10)
project(Listat_Software__tests)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(lib/googletest)
add_subdirectory(test/parcer)
#include_directories(lib/googletest/googletest/include)
#include_directories(lib/googletest/googlemock/include)


#set(SOURCE_FILES1 t_main.cpp test/parcer/test_parcer.cpp)
#add_executable(App-GoogleTest ${SOURCE_FILES} ${SOURCE_FILES1})
#target_link_libraries(App-GoogleTest gtest gtest_main)