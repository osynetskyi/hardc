#include "minunit.h"
#include <lcthw/bstrlib.h>

static bstring bstr = NULL;
const char *test1 = "test1 data";
const char *test2 = "test2 data";
const char *data = "data";
const char *vata = "vata";


char *test_bfromc()
{
	bstr = bfromcstr(test1);
	mu_assert(blength(bstr) == 10, "Size is wrong.");
	char *res = malloc(sizeof(char) * blength(bstr));
	bassigncstr(bstr, res);
	mu_assert(strcmp(res, test1), "Strings are not equal.");
	
	free(res);
	bdestroy(bstr);
	return NULL;
}

char *test_blk2bstr()
{
	bstr = bfromcstr(test1);
	bstring try = blk2bstr(test1, 10);
	mu_assert(bstricmp(bstr, try) == 0, "bStrings are not equal.");
	mu_assert(biseq(bstr, try), "bStrings are not equal.");
	
	bdestroy(try);
	bdestroy(bstr);
	return NULL;
}

char *test_bconcat()
{
	bstr = bfromcstr(test1);
	bstring try = bfromcstr(data);
	int l1 = blength(bstr);
	int l2 = blength(try);
	int rc = bconcat(bstr, try);

	mu_assert(rc == 0, "Concat returned an error.");
	mu_assert(blength(bstr) == l1 + l2, "Length is wrong.");
	
	bdestroy(try);
	bdestroy(bstr);
	return NULL;
}

char *test_bassign()
{
	bstr = bfromcstr(test1);
	bstring try = NULL;
	bassign(try, bstr);
	bstring copy = bstrcpy(try);
	mu_assert(biseq(try, bstr), "Not equal after assignment.");
	mu_assert(biseq(copy, bstr), "Not equal after copy.");

	bdestroy(try);
	bdestroy(copy);
	bdestroy(bstr);
	return NULL;
}

char *test_bfindreplace()
{
	bstr = bfromcstr(test2);
	bstring pattern = bfromcstr(data);
	bstring replace = bfromcstr(vata);
	int rc = bfindreplace(bstr, pattern, replace, 0);
	mu_assert(rc == 0, "Replace did not go well.");

	int pos = binstr(bstr, 0, replace);
	mu_assert(pos == 6, "Find returned incorrect result.");

	bdestroy(pattern);
	bdestroy(replace);
	bdestroy(bstr);
	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_bfromc);
	mu_run_test(test_blk2bstr);
	mu_run_test(test_bconcat);
	mu_run_test(test_bassign);
	mu_run_test(test_bfindreplace);

	return NULL;
}

RUN_TESTS(all_tests);
