cmake_minimum_required(VERSION 3.12)
project(main_project)

add_executable(main main.cpp)

find_library(CSVPARSER_LIB NAMES csvparser PATHS ${CMAKE_CURRENT_SOURCE_DIR}/../src/csvparser)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../src)

target_link_libraries(main ${CSVPARSER_LIB})
