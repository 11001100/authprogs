project (cutest C)


set (HDRS			CuTest.h)
source_group ("include" FILES ${HDRS})

set (SRCS			CuTest.c)
source_group ("src" FILES ${SRCS})


if (MSVC)
	add_definitions (-D_CRT_NONSTDC_NO_DEPRECATE)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS)
endif ()


add_library (${PROJECT_NAME} STATIC ${HDRS} ${SRCS})



set_property(TARGET ${PROJECT_NAME} PROPERTY FOLDER "authprogs/test/unit")