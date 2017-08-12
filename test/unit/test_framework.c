#include <stdio.h>
#include <string.h>

#include "src/ap_defs.h"

#include "test_framework.h"


const char				*data_dir			= NULL;


int test_framework_init (int argc, char *argv[])
{
	int				rc					= TEST_NO_ERROR;
	int				i;

	if (argc != 3)
	{
		rc = TEST_ERROR_INIT;
		goto finish;
	}

	for (i = 1; i < argc; i++)
	{
		if (strcmp (argv[i], "--data-dir") == 0)
		{
			if (i < argc - 1)
			{
				data_dir = argv[++i];
			}
			else
			{
				rc = TEST_ERROR_INIT;
				goto finish;
			}
		}
	}

	if (data_dir == NULL)
	{
		rc = TEST_ERROR_INIT;
		goto finish;
	}


finish:
	return rc;
}


int test_framework_uninit (int argc, char *argv[], int result)
{
	AP_UNUSED_VAR (argc);
	AP_UNUSED_VAR (argv);
	AP_UNUSED_VAR (result);

	return TEST_NO_ERROR;
}


int test_framework (int argc, char *argv[])
{
	AP_UNUSED_VAR (argc);
	AP_UNUSED_VAR (argv);

	return TEST_NO_ERROR;
}
