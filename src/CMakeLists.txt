cmake_minimum_required(VERSION 3.12)
project(libraries)

set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)
find_package(Boost 1.83 REQUIRED)
set(LIB_TO_COMPILE "option_value" CACHE STRING "Some user specified option")

if(LIB_TO_COMPILE STREQUAL "csvparser")
	add_library(csvparser SHARED csvparser.hpp csvparser.cpp)
	target_link_libraries(csvparser ${Boost_LIBRARIES})
endif()

if(LIB_TO_COMPILE STREQUAL "odesolver")
		add_library(odesolver SHARED odesolver.hpp odesolver.cpp)
		# target for eigen
endif()

