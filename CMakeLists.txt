cmake_minimum_required(VERSION 2.8.9)

project(onlinecourses_project)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")	

FIND_PACKAGE(Threads REQUIRED)

option( WITH_TESTS "Build together with all available unitTest" ON )

if(WITH_TESTS)
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})
endif(WITH_TESTS)

include_directories(include)
include_directories(database)
include_directories(templates)
include_directories(logger/include)

set(LIBS 
	${LIBS}
	${CMAKE_THREAD_LIBS_INIT}
)

file(GLOB MAIN_SRC "main.cpp")

file(GLOB SOURCES "logger/src/*.cpp" "src/*.cpp" "database/*.cpp")
add_executable(olcproject ${MAIN_SRC} ${SOURCES})
TARGET_LINK_LIBRARIES(olcproject ${LIBS})

if(WITH_TESTS)
include_directories(database/test)

set(LIBS 
	${LIBS}
	${GTEST_MAIN_LIBRARIES}
    ${GTEST_BOTH_LIBRARIES}
    ${GTEST_LIBRARIES}
	#GTest::GTest
	#GTest::Main
)

file(GLOB TEST_SRC "database/test/*.cpp")
add_executable(unit_test ${TEST_SRC} ${SOURCES})
TARGET_LINK_LIBRARIES(unit_test ${LIBS})
endif(WITH_TESTS)
