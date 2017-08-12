project (authprogs_test C)


set (HDRS	test_framework.h)
source_group ("include" FILES ${HDRS})

set (SRCS	test_framework.c
			test_str.c)
source_group ("src" FILES ${SRCS})


if (MSVC)
	add_definitions (-D_CRT_NONSTDC_NO_DEPRECATE)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS)
endif ()


include_directories (${CMAKE_CURRENT_SOURCE_DIR})
include_directories (${CMAKE_SOURCE_DIR})


set (CMAKE_TESTDRIVER_BEFORE_TESTMAIN "int rc = test_framework_init(ac, av); if (rc != TEST_NO_ERROR) return rc;")
set (CMAKE_TESTDRIVER_AFTER_TESTMAIN "rc = test_framework_uninit(ac, av, result); if (rc != TEST_NO_ERROR) return rc;")
create_test_sourcelist (TESTS ${PROJECT_NAME}_driver.c ${HDRS} ${SRCS} EXTRA_INCLUDE test_framework.h)


add_executable (${PROJECT_NAME}_driver ${TESTS})
target_link_libraries(${PROJECT_NAME}_driver authprogs_lib cutest)


set_property (TARGET ${PROJECT_NAME}_driver PROPERTY FOLDER "authprogs/test/unit")


list (REMOVE_ITEM TESTS ${PROJECT_NAME}_driver.c test_framework.c)
list (REMOVE_ITEM TESTS test_framework.h)


# copy input data for tests
add_test (NAME authprogs_unit_test_copy_data
			COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/data ${CMAKE_CURRENT_BINARY_DIR}/data)

foreach (TEST ${TESTS})
	get_filename_component (TEST_NAME_WE ${TEST} NAME_WE)
			 
	add_test (NAME authprogs_unit_${TEST_NAME_WE}
				COMMAND $<TARGET_FILE:${PROJECT_NAME}_driver> ${TEST_NAME_WE} --data-dir ${CMAKE_CURRENT_BINARY_DIR}/data/${TEST_NAME_WE})
endforeach ()
