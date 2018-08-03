cmake_minimum_required(VERSION 3.10)

project(Listat_Software__lib)

set(HEADER_FILES
        include/defines.h
        include/application.hpp
        include/calc_prime_th.hpp
        include/xml_node.hpp
        include/xml_parser.hpp
        include/utils.h
        )

set(SOURCE_FILES
        application.cpp
        calc_prime_th.cpp
        xml_node.cpp
        xml_parser.cpp
        utils.cpp
        )

add_library(Listat_Software__lib STATIC ${SOURCE_FILES} ${HEADER_FILES})