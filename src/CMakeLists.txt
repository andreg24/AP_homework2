cmake_minimum_required(VERSION 3.12)
project(libraries)

set(LIB_TO_COMPILE "option_value" CACHE STRING "Some user specified option")

if(LIB_TO_COMPILE STREQUAL "csvparser")
	set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../extlib)
	find_package(Boost 1.83 REQUIRED)
	add_library(csvparser SHARED csvparser.hpp csvparser.cpp)
	target_link_libraries(csvparser ${Boost_LIBRARIES})
endif()

if(LIB_TO_COMPILE STREQUAL "odesolver")
	set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../extlib)
	find_package(Eigen3 3.4 REQUIRED)
	add_library(odesolver SHARED odesolver.hpp odesolver.cpp)
	target_link_libraries(odesolver Eigen3::Eigen)
endif()

