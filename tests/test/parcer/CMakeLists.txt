# For Parcer test
configure_file(test_00.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_01.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_02.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_03.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY) #корректный
configure_file(test_04.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_05.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_06.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_07.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY) #корректный
configure_file(test_08.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(test_09.xml ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)

add_executable(Listat_Software__tests_parcer test_parcer.cpp)

target_link_libraries(Listat_Software__tests_parcer gtest gtest_main)
target_link_libraries(Listat_Software__tests_parcer Listat_Software__lib)