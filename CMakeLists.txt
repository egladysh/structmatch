cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(fuzzy LANGUAGES CXX)

message( STATUS "Generator - ${CMAKE_GENERATOR}")
message( STATUS "Build type - ${CMAKE_BUILD_TYPE}")

if( APPLE )
	set( CMAKE_CXX_FLAGS "-std=c++1z -stdlib=libc++ -Wall" )
else()
	set( CMAKE_CXX_FLAGS "-std=c++1z -Wall -pthread" )
endif()


file(GLOB src src/*.cpp src/*.h)

add_executable(${PROJECT_NAME} ${src})
