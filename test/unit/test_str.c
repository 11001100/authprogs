#include <string.h>
#include <stdio.h>

#include "test/cutest/CuTest.h"

#include "src/ap_defs.h"
#include "src/ap_str.h"

#include "test_framework.h"


static void tc_ap_str_trim_head_from_set (CuTest* tc)
{
	char	buf_str[1024];
	char	buf_set[1024];

	strcpy (buf_set, " \t");

	CuAssertStrEquals_Msg (tc, "strings should be equal", NULL,							ap_str_trim_head_from_set (NULL, NULL));

	strcpy (buf_str, "");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, " ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "  ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "  ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "\t\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, " a");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "  a");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "   a");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "\ta");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "\t\ta");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "\t\t\ta");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, " a ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a ",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "a ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a ",							ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "a  ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a  ",						ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "a   ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a   ",						ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "a\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a\t",						ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "a\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a\t\t",						ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "a\t\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a\t\t\t",					ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, " a\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a\t",						ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, " a \t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a \t",						ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, " \t \t \ta \t \t \t \t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a \t \t \t \t",				ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "aaa bbb ccc");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "aaa bbb ccc",				ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "         aaa bbb ccc");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "aaa bbb ccc",				ap_str_trim_head_from_set (buf_str, buf_set));

	strcpy (buf_str, "  \t\t  \t  \taaa bbb ccc");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "aaa bbb ccc",				ap_str_trim_head_from_set (buf_str, " \t"));

	strcpy (buf_str, "  \t\t  \t  \taaa bbb ccc \t \t \t   ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "aaa bbb ccc \t \t \t   ",	ap_str_trim_head_from_set (buf_str, " \t"));
}


static void tc_ap_str_trim_tail_from_set (CuTest* tc)
{
	CuAssertStrEquals_Msg (tc, "strings should be equal", NULL,							ap_str_trim_tail_from_set (NULL, " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (" ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("  ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("   ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("\t\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("\t\t\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (" a", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "  a",						ap_str_trim_tail_from_set ("  a", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "   a",						ap_str_trim_tail_from_set ("   a", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "\ta",						ap_str_trim_tail_from_set ("\ta", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "\t\ta",						ap_str_trim_tail_from_set ("\t\ta", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "\t\t\ta",					ap_str_trim_tail_from_set ("\t\t\ta", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (" a ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set ("a ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set ("a  ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set ("a   ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set ("a\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set ("a\t\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set ("a\t\t\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (" a ", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (" a\t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (" a \t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", " \t \t \ta",					ap_str_trim_tail_from_set (" \t \t \ta \t \t \t \t", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "aaa bbb ccc",				ap_str_trim_tail_from_set ("aaa bbb ccc", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "         aaa bbb ccc",		ap_str_trim_tail_from_set ("         aaa bbb ccc", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "  \t\t  \t  \taaa bbb ccc",	ap_str_trim_tail_from_set ("  \t\t  \t  \taaa bbb ccc", " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "  \t\t  \t  \taaa bbb ccc",	ap_str_trim_tail_from_set ("  \t\t  \t  \taaa bbb ccc \t \t \t   ", " \t"));
}


/*
static void tc_file_copy_raw(CuTest* tc)
{
	//int			rc;
	char		in_name[4096] = { '\0' };
	char		out_name[4096] = { '\0' };

	strcat (in_name, data_dir);
	strcat (in_name, "/");
	strcat (in_name, "tc_file_copy_raw");

	strcat (out_name, data_dir);
	strcat (out_name, "/");
	strcat (out_name, "tc_file_copy_raw_out");
}
*/


int test_str (int argc, char *argv[])
{
	CuString	*output			= CuStringNew();
	CuSuite		*suite			= CuSuiteNew();
	int			failCount;

	AP_UNUSED_VAR (argc);
	AP_UNUSED_VAR (argv);

	SUITE_ADD_TEST (suite, tc_ap_str_trim_head_from_set);
	//SUITE_ADD_TEST (suite, tc_ap_str_trim_tail_from_set);
	
	CuSuiteRun (suite);
	CuSuiteSummary (suite, output);
	CuSuiteDetails (suite, output);

	printf ("%s\n", output->buffer);

	failCount = suite->failCount;

	CuSuiteDelete (suite);
	CuStringDelete (output);

	return failCount;
}
