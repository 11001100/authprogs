#ifndef _TEST_FRAMEWORK_H_
#define _TEST_FRAMEWORK_H_


enum
{
	TEST_NO_ERROR				= 0,
	TEST_ERROR_GENERIC,
	TEST_ERROR_INIT,
	TEST_ERROR_UNINIT
};


extern const char			*data_dir;


int test_framework_init		(int argc, char *argv[]);
int test_framework_uninit	(int argc, char *argv[], int result);


#endif

