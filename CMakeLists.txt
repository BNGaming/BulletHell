cmake_minimum_required(VERSION 2.6)
project(BulletHell)

MESSAGE( STATUS "CMAKE_VERSION: " ${CMAKE_VERSION} )

#Windows-specific setup before finding packages
if(WIN32)
	message(STATUS "Including \"${PROJECT_SOURCE_DIR}/VS/Pre/CMakeLists.txt\"")
	include("${PROJECT_SOURCE_DIR}/VS/Pre/CMakeLists.txt")
endif()


add_subdirectory(${PROJECT_SOURCE_DIR}/src)
include_directories("src")

message(STATUS "Setting CMAKE_MODULE_PATH: ${CMAKE_SOURCE_DIR}/cmake/Modules/ ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH}")
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} )

#Find Packages
##SFML
find_package(SFML 2.5 REQUIRED window system graphics)
message(STATUS "SFML found: ${SFML_LIBRARIES}")

##Boost
find_package(Boost REQUIRED)
message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")

##Freetype, Doesn't support CMAKE upstream
#find_package(Freetype REQUIRED freetype)
#message(STATUS "Freetype found: ${FREETYPE_LIBRARY}")
#message(STATUS "Freetype found: ${FREETYPE_LIBRARIES}")
#find_path(FREETYPE_INCLUDE_DIR freetype/freetype.h)
#find_library(FREETYPE_LIBRARY freetype)
#message(STATUS "Freetype Found Include Dir: ${FREETYPE_INCLUDE_DIR}")
#message(STATUS "Freetype Found Library: ${FREETYPE_LIBRARY}")


#Include found packages' include dirs
##SFML
message(STATUS "Including SFML from: ${SFML_INCLUDE_DIR}")
include_directories(${SFML_INCLUDE_DIR})

##Boost
message(STATUS "Including Boost from: ${Boost_INCLUDE_DIRS}")
include_directories(${Boost_INCLUDE_DIRS})

##Freetype
#message(STATUS "Including Freetype from: ${FREETYPE_INCLUDE_DIRS}")
#include_directories(${FREETYPE_INCLUDE_DIRS})


#Compiler flags
if(NOT MSVC)
    list(APPEND CMAKE_CXX_FLAGS "-std=c++14")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()
message(STATUS "CMAKE_CXX_FLAGS: \"${CMAKE_CXX_FLAGS}\"")

#Add executable and link libraries
add_executable(bullet ${SOURCES})
target_link_libraries(bullet ${SFML_LIBRARIES} ${Boost_LIBRARIES})
#target_link_libraries(bullet debug ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Boost_LIBRARIES})


#Windows-specific settings for after an executable has been specified
if(WIN32)
	message(STATUS "Including: \"${PROJECT_SOURCE_DIR}/VS/Post/CMakeLists.txt\"")
	include("${PROJECT_SOURCE_DIR}/VS/Post/CMakeLists.txt")
endif()

message(STATUS "End of primary CMakeLists.txt file")
