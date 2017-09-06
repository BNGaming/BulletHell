cmake_minimum_required(VERSION 2.6)
project(BulletHell)

add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories("src")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

find_package(SFML 2.4 REQUIRED window system graphics)

include_directories(${SFML_INCLUDE_DIR})

list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

add_executable(bullet ${SOURCES})
target_link_libraries(bullet ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
