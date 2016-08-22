cmake_minimum_required(VERSION 2.8.6)
project(zieds)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_library(zieds SHARED ${SOURCES})

install(TARGETS zieds DESTINATION /usr/lib)
