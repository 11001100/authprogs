#ifndef _AP_LOG_H_
#define _AP_LOG_H_


#include <stdio.h>


#define AP_LOG_BUF_SIZE				4096
#define AP_LOG_TIME_FORMAT			"%Y/%m/%d %H:%M:%S"


typedef enum _AP_LOG_LEVEL
{
	AP_LOG_LEVEL_QUIET				= 0,
	AP_LOG_LEVEL_ERROR,
	AP_LOG_LEVEL_DENIED_COMMAND,
	AP_LOG_LEVEL_ALLOWED_COMMAND,
	AP_LOG_LEVEL_DEBUG,
	AP_LOG_LEVEL_TRACE
} AP_LOG_LEVEL;


#define ap_error(...)				ap_log (AP_LOG_LEVEL_ERROR, __VA_ARGS__)
#define ap_denied(...)				ap_log (AP_LOG_LEVEL_DENIED_COMMAND, __VA_ARGS__)
#define ap_allowed(...)				ap_log (AP_LOG_LEVEL_ALLOWED_COMMAND, __VA_ARGS__)
#define ap_debug(...)				ap_log (AP_LOG_LEVEL_DEBUG, __VA_ARGS__)
#define ap_trace(...)				ap_log (AP_LOG_LEVEL_TRACE, __VA_ARGS__)


int				ap_log_init			(void);
void			ap_log_set_output	(FILE *file);
FILE *			ap_log_get_output	(void);
void			ap_log_set_level	(AP_LOG_LEVEL level);
AP_LOG_LEVEL	ap_log_get_level	(void);
void			ap_log				(AP_LOG_LEVEL level, const char *p_format, ...);
void			ap_log_flush		(void);


#endif

