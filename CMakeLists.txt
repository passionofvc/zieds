cmake_minimum_required(VERSION 2.8.6)
project(zieds)
set(CMAKE_BUILD_TYPE Release)

include_directories(include)

file(GLOB SOURCES "src/*.c")

add_library(zieds SHARED ${SOURCES})

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

install(TARGETS zieds DESTINATION /usr/lib)
