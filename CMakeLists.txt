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

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/" "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH} )

#Find Packages
find_package(SFML 2.4 REQUIRED window system graphics)

find_package(Boost)
if(NOT Boost_FOUND)
	message(FATAL_ERROR "Boost is required for building, but could not be found by CMake.")
endif()
message(STATUS "Boost found: ${Boost_INCLUDE_DIRS}")


#Include found packages
message(STATUS "Including SFML from: ${SFML_INCLUDE_DIRS}")
include_directories(${SFML_INCLUDE_DIR})
message(STATUS "Including Boost from: ${Boost_INCLUDE_DIRS}")
include_directories(${Boost_INCLUDE_DIRS})


#Compiler flags
if(NOT MSVC)
    list(APPEND CMAKE_CXX_FLAGS "-std=c++14")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif()
message(STATUS "CMAKE_CXX_FLAGS: \"${CMAKE_CXX_FLAGS}\"")


add_executable(bullet ${SOURCES})
target_link_libraries(bullet ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} ${Boost_LIBRARIES})

#Windows-specific settings for after an executable has been specified
if(WIN32)
	message(STATUS "Including: \"${PROJECT_SOURCE_DIR}/VS/Post/CMakeLists.txt\"")
	include("${PROJECT_SOURCE_DIR}/VS/Post/CMakeLists.txt")
endif()

message(STATUS "End of primary CMakeLists.txt file")
