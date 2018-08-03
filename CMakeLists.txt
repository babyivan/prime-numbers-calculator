cmake_minimum_required(VERSION 3.10)
project(Listat_Software__run)
set(CMAKE_CXX_STANDARD 11)

configure_file(file.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

#https://stackoverflow.com/questions/11783932/how-to-add-linker-or-compile-flag-in-cmake-file
# Для потоков обязательно нужен флаг "pthread"
set(GCC_COVERAGE_COMPILE_FLAGS "-pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

set(SOURCE_FILES main.cpp)

add_executable(Listat_Software__run ${SOURCE_FILES})

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(Listat_Software__run Listat_Software__lib)