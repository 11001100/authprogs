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
	char	buf_str[1024];

	CuAssertStrEquals_Msg (tc, "strings should be equal", NULL,							ap_str_trim_tail_from_set (NULL, " \t"));
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set ("", " \t"));

	strcpy (buf_str, " ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "  ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "   ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "\t\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, " a");
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "  a");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "  a",						ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "   a");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "   a",						ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "\ta");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "\ta",						ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "\t\ta");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "\t\ta",						ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "\t\t\ta");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "\t\t\ta",					ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, " a ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "a ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "a  ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "a   ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "a\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "a\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "a\t\t\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, " a\t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, " a \t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", " a",							ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, " \t \t \ta \t \t \t \t");
	CuAssertStrEquals_Msg (tc, "strings should be equal", " \t \t \ta",					ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "aaa bbb ccc");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "aaa bbb ccc",				ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "         aaa bbb ccc");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "         aaa bbb ccc",		ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "  \t\t  \t  \taaa bbb ccc");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "  \t\t  \t  \taaa bbb ccc",	ap_str_trim_tail_from_set (buf_str, " \t"));

	strcpy (buf_str, "  \t\t  \t  \taaa bbb ccc \t \t \t   ");
	CuAssertStrEquals_Msg (tc, "strings should be equal", "  \t\t  \t  \taaa bbb ccc",	ap_str_trim_tail_from_set (buf_str, " \t"));
}


static void tc_ap_str_match (CuTest* tc)
{
	const char	*invalid_chars	= ";{}|`()&";

	// should return error
	// simple
	CuAssert (tc, "should return error", ap_str_match(NULL, NULL, invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match(NULL, "0123456789", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", NULL, invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("", "0123456789", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "0123", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123", "0123456789", invalid_chars) != 0);
	
	// ?
	CuAssert (tc, "should return error", ap_str_match("0123456789", "?", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "??", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "01?", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "01?3", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match(";", "?", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match(";{}", "??", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("|", "?", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("01&", "01?", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("012)45", "012?45", invalid_chars) != 0);

	// *
	CuAssert (tc, "should return error", ap_str_match("0123456789", "*a", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "a*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "0a*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "0*a", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "0*a*9", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "*9a", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "0*9a", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "0*a9", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "***a", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "a***", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0123456789", "012345678*a", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("|", "*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|", "*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2", "*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|", "0*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2", "0*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2", "*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2", "0*2", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|23", "0*2*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2|", "0*2*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2|4", "0*2*", invalid_chars) != 0);
	CuAssert (tc, "should return error", ap_str_match("0|2|45", "0*2*5", invalid_chars) != 0);
		
	// should match
	// simple
	CuAssert (tc, "should match", ap_str_match("", "", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "0123456789", invalid_chars) == 0);

	// ?
	CuAssert (tc, "should match", ap_str_match("0", "?", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("01", "0?", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "??????????", invalid_chars) == 0);

	// *
	CuAssert (tc, "should match", ap_str_match("", "*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0", "*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("01", "01*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("01", "0*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("01", "*1", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "0*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "0*9", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "*6789", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "01234*6789", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "0*4*9", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "*4*6*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "0*2345678*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "01234*678*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "01234*67*9", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "01234****6789", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "01234***56789", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match("0123456789", "012*34***56789*", invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match(
		"/usr/bin/sudo /sbin/zfs send -I 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_08:00:02_hourly' 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_09:00:02_hourly' | /usr/bin/mbuffer  -q -s 128k -m 16M 2>/dev/null",
		"/usr/bin/sudo /sbin/zfs send -I '*' '*' | /usr/bin/mbuffer  -q -s 128k -m 16M 2>/dev/null",
		invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match(
		"/usr/bin/sudo /sbin/zfs send -I 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_08:00:02_hourly' 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_09:00:02_hourly' | /usr/bin/mbuffer  -q -s 128k -m 16M 2>/dev/null",
		"/usr/bin/sudo /sbin/zfs send * | /usr/bin/mbuffer  -q -s 128k -m 16M 2>/dev/null",
		invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match(
		"/usr/bin/sudo /sbin/zfs send -I 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_08:00:02_hourly' 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_09:00:02_hourly' | /usr/bin/mbuffer  -q -s 128k -m 16M 2>/dev/null",
		"/usr/bin/sudo /sbin/zfs send * | /usr/bin/mbuffer *"
		, invalid_chars) == 0);
	CuAssert (tc, "should match", ap_str_match(
		"/usr/bin/sudo /sbin/zfs send -I 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_08:00:02_hourly' 'rpool/ROOT/ubuntu'@'autosnap_2018-11-23_09:00:02_hourly' | /usr/bin/mbuffer  -q -s 128k -m 16M 2>/dev/null",
		"/usr/bin/sudo /sbin/zfs send * | *",
		invalid_chars) == 0);
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
	SUITE_ADD_TEST (suite, tc_ap_str_trim_tail_from_set);
	SUITE_ADD_TEST (suite, tc_ap_str_match);
	
	CuSuiteRun (suite);
	CuSuiteSummary (suite, output);
	CuSuiteDetails (suite, output);

	printf ("%s\n", output->buffer);

	failCount = suite->failCount;

	CuSuiteDelete (suite);
	CuStringDelete (output);

	return failCount;
}
