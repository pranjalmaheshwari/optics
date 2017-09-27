cmake_minimum_required(VERSION 2.8.12)

project(hw3)

#########################################################
# FIND C++11 Support
#########################################################
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
		message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -fopenmp -DDIM=${DIM}")

find_package(Boost COMPONENTS system filesystem regex REQUIRED)

# include the important directories and boost library
include_directories(include/)


# libraries

add_library(optics-cc src/optics.cpp)


# executables

add_executable(optics scripts/main.cpp)


# link executables

target_link_libraries(optics optics-cc
							${Boost_LIBRARIES})
