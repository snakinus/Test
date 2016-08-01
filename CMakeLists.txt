cmake_minimum_required(VERSION 3.5)
project(classy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package(OpenGL REQUIRED)
find_package(Threads REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(xge REQUIRED)

file(GLOB_RECURSE HEADERS MGame.h)
file(GLOB_RECURSE SOURCES main.cpp MGame.cpp)
add_executable(classy ${HEADERS} ${SOURCES})
target_link_libraries(classy ${XGE_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})