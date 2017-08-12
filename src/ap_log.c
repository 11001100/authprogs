#include <time.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "ap.h"
#include "ap_str.h"
#include "ap_log.h"


static FILE				*ap_log_file					= NULL;
static AP_LOG_LEVEL		ap_log_level					= AP_LOG_LEVEL_ALLOWED_COMMAND;
static char				ap_log_buf[AP_LOG_BUF_SIZE];


int ap_log_init ()
{
	ap_log_file = stdout;
	ap_log_level = AP_LOG_LEVEL_ALLOWED_COMMAND;

	return AP_NO_ERROR;
}


void ap_log_set_output (FILE *file)
{
	ap_log_file = file;
}


FILE * ap_log_get_output ()
{
	return ap_log_file;
}


void ap_log_set_level (AP_LOG_LEVEL level)
{
	ap_log_level = level;
}


AP_LOG_LEVEL ap_log_get_level ()
{
	return ap_log_level;
}


static const char * level_to_str (unsigned int level)
{
	const char *str = "unknown log level";

	switch (level)
	{
		case AP_LOG_LEVEL_QUIET:
		{
			str = "quiet";

			break;
		}

		case AP_LOG_LEVEL_ERROR:
		{
			str = "error";

			break;
		}

		case AP_LOG_LEVEL_DENIED_COMMAND :
		{
			str = "denied";

			break;
		}

		case AP_LOG_LEVEL_ALLOWED_COMMAND :
		{
			str = "allowed";

			break;
		}

		case AP_LOG_LEVEL_DEBUG:
		{
			str = "debug";

			break;
		}

		case AP_LOG_LEVEL_TRACE:
		{
			str = "trace";

			break;
		}
	}

	return str;
}


void ap_log (AP_LOG_LEVEL level, const char *format, ...)
{
	time_t		t;
	struct tm	*tm					= NULL;
	size_t		size;
	size_t		log_buf_size		= sizeof (ap_log_buf);
	va_list		args;
	size_t		log_buf_len			= 0;

	if (format == NULL)
	{
		goto finish;
	}

	if (level > ap_log_level)
	{
		goto finish;
	}

	t = time (NULL);
	if (t != (time_t) -1)
	{
		tm = localtime (&t);
		if (tm != NULL)
		{
			size = strftime (ap_log_buf, log_buf_size, AP_LOG_TIME_FORMAT, tm);
			if (size == 0)
			{
				ap_str_strlcpy (ap_log_buf, "strftime error", log_buf_size);
			}
		}
	}

	ap_str_strlcat (ap_log_buf, " [", log_buf_size);
	ap_str_strlcat (ap_log_buf, level_to_str (level), log_buf_size);
	ap_str_strlcat (ap_log_buf, "] ", log_buf_size);

	va_start (args, format);

	log_buf_len = strlen (ap_log_buf);
	vsnprintf (ap_log_buf + log_buf_len, log_buf_size - log_buf_len, format, args);

	va_end (args);

	fprintf (ap_log_file, "%s", ap_log_buf);

	fflush (ap_log_file);

finish:
	return;
}


void ap_log_flush (void)
{
	fflush (ap_log_file);
}