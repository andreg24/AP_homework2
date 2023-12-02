cmake_minimum_required(VERSION 3.12)
project(Homework_2)

add_compile_options(-std=c++17 -Wall -Wextra -Wpedantic -Werror -Wno-deprecated-copy)

# --COMPILE CSVPARSER SHARED LIBRARY--

### find Boost
find_package(Boost 1.82.0 REQUIRED)
if(Boost_FOUND)
    message("Boost found")
    include_directories(${BOOST_ROOT}/boost/include)
else()
    message(FATAL_ERROR "Boost not found")
endif()

### compile csvparser.so
add_library(csvparser SHARED src/csvparser.hpp src/csvparser.cpp)

### include header files for the library
target_include_directories(csvparser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

### link against Boost and any other necessary libraries
target_link_libraries(csvparser PRIVATE ${Boost_LIBRARIES})


# --COMPILE ODESOLVER SHARED LIBRARY--

## find Eigen
set(EIGEN_PATH "option_value" CACHE STRING "Some user specified option")
find_package(Eigen3 PATHS ${EIGEN_PATH} REQUIRED)
if(Eigen3_FOUND)
	message("Eigen3 found")
else()
	message(FATAL_ERROR "Eigen3 not found")
endif()
### compile odesolver.so
add_library(odesolver SHARED src/odesolver.hpp src/odesolver.cpp)

target_include_directories(odesolver PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src ${EIGEN3_INCLUDE_DIR})
message("${EIGEN3_INCLUDE_DIR}")
# --BUILD EXECUTABLES--

add_executable(maincsv apps/maincsv.cpp)

### link against library
target_link_libraries(maincsv PRIVATE csvparser)

add_executable(mainode apps/mainode.cpp)

# Link against the main library
target_link_libraries(mainode PRIVATE odesolver)

