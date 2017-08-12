cmake_minimum_required (VERSION 2.8)


project (authprogs C)


set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")


if (MSVC AND CMAKE_CONFIGURATION_TYPES)
	set (EXECUTABLE_OUTPUT_PATH		${CMAKE_BINARY_DIR})
	set (LIBRARY_OUTPUT_PATH		${CMAKE_BINARY_DIR})
else ()
	set (EXECUTABLE_OUTPUT_PATH		${CMAKE_BINARY_DIR}/bin)
	set (LIBRARY_OUTPUT_PATH		${CMAKE_BINARY_DIR}/bin)
endif ()


enable_testing ()


add_subdirectory (src)
add_subdirectory (test)
