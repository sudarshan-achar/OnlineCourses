cmake_minimum_required(VERSION 2.8.9)

project(onlinecourses_project)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")	

FIND_PACKAGE(Threads REQUIRED)

set(LIBS 
	${LIBS}
	${CMAKE_THREAD_LIBS_INIT}
)

include_directories(include)
include_directories(database)
include_directories(templates)
include_directories(logger/include)

file(GLOB SOURCES "main.cpp" "logger/src/*.cpp" "src/*.cpp" "database/*.cpp")

add_executable(olcproject ${SOURCES})

TARGET_LINK_LIBRARIES(olcproject ${LIBS})
