cmake_minimum_required(VERSION 3.12)
project(try_boost)

# Set the path to the Boost installation in the extlib folder
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/../proj/extlib)

# Find the Boost components you need
find_package(Boost 1.82.0 REQUIRED)

if(Boost_FOUND)
    message("Boost found")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../proj/extlib/boost/include)
else()
    message(FATAL_ERROR "Boost not found")
endif()

# Compile main.cpp as a shared library
add_library(csvparser SHARED src/csvparser.hpp src/csvparser.cpp)

# Include header files for the library
target_include_directories(csvparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Link against Boost and any other necessary libraries
target_link_libraries(csvparser PRIVATE ${Boost_LIBRARIES})

# Build the executable using another_file.cpp
add_executable(main apps/main.cpp)

# Link against the main library
target_link_libraries(main PRIVATE csvparser)
