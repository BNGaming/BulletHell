#Begin file
message(STATUS "Start of Post/CMakeLists.txt file")

#Make our build directory sensible
set_target_properties(bullet PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/build")
get_target_property(BULLET_RUNTIME_OUTPUT_DIR bullet RUNTIME_OUTPUT_DIRECTORY)
message(STATUS "Set Build directory to be ${BULLET_RUNTIME_OUTPUT_DIR}")

#Put DLLs with the executable after build
#message(STATUS "Adding post-Build command to copy DLLs from ${PROJECT_SOURCE_DIR}/extlibs/${ARCHITECTURE}/bin to ${BULLET_RUNTIME_OUTPUT_DIR}")
#add_custom_command(TARGET bullet POST_BUILD
#	COMMAND ${CMAKE_COMMAND} -E copy_directory
#		"${PROJECT_SOURCE_DIR}/extlibs/${ARCHITECTURE}/bin"
#		"${BULLET_RUNTIME_OUTPUT_DIR}")

#Put Resources with the executable after build
message(STATUS "Adding post-Build command to copy Resources from ${PROJECT_SOURCE_DIR}/resources to ${BULLET_RUNTIME_OUTPUT_DIR}/resources")
add_custom_command(TARGET bullet POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		"${PROJECT_SOURCE_DIR}/resources"
		"${BULLET_RUNTIME_OUTPUT_DIR}/resources")

#End file
message(STATUS "End of Post/CMakeLists.txt file")