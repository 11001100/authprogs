project (authprogs C)


set (HDRS	ap.h
			ap_defs.h
			ap_log.h
			ap_str.h
			ap_version.h)

source_group ("include" FILES ${HDRS})

set (SRCS	ap.c
			ap_log.c
			ap_str.c)

source_group ("src" FILES ${SRCS})


if (MSVC)
	add_definitions (-D_CRT_NONSTDC_NO_DEPRECATE)
	add_definitions (-D_CRT_SECURE_NO_WARNINGS)
endif ()


add_executable (${PROJECT_NAME} ${HDRS} ${SRCS})

set_property (TARGET ${PROJECT_NAME} PROPERTY FOLDER "authprogs")


add_library (${PROJECT_NAME}_lib STATIC ${HDRS} ${SRCS})

set_property (TARGET ${PROJECT_NAME}_lib PROPERTY FOLDER "authprogs")
