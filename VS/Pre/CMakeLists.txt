#Root directory for any external libraries
set(EXTERNAL_LIBS_DIR "D:/Libraries")
	
#SFML
set(SFML_VERSION_NUMBER "2.4.2")
set(SFML_ROOT "${EXTERNAL_LIBS_DIR}/SFML/${ARCHITECTURE}/SFML-${SFML_VERSION_NUMBER}")
	
#Module path for CMAKE
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
