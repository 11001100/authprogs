#ifndef _AP_DEFS_H_
#define _AP_DEFS_H_


#if defined (_WIN32)
	typedef unsigned __int32			uint32_t;
#endif

typedef unsigned char					BOOL;

#if !defined (FALSE)
#	define FALSE  0
#	define TRUE   !FALSE
#endif

#define AP_STR_SIZE						1024

#define AP_UNUSED_VAR(x)				(void) sizeof (x)

#define AP_VALIDATE_PTR_ARGUMENT(ptr)									\
{																		\
	if (ptr == NULL)													\
	{																	\
		ap_log (AP_LOG_LEVEL_ERROR, "Invalid argument: " #ptr "\n");	\
		rc = AP_ERROR_INVALID_ARGUMENT;									\
																		\
		goto finish;													\
	}																	\
}

#if defined (_WIN32)
#	define strtok_r						strtok_s
#endif


#endif
