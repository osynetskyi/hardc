#include "minunit.h"
#include <lcthw/darray_algos.h>

int testcmp(char **a, char **b)
{
	return strcmp(*a, *b);
}

DArray *create_words()
{
	DArray *result = DArray_create(0, 5);
	char *words[] = {"asdfasfd", "werwar", "13234", "xasdfasfd", "oioj"};
	int i = 0;

	for(i = 0; i < 5; i++) {
		DArray_push(result, words[i]);
	}

	return result;
}

int is_sorted(DArray *array)
{
	int i = 0;

	for(i = 0; i < DArray_count(array) - 1; i++) {
		if(strcmp(DArray_get(array, i), DArray_get(array, i+1)) > 0) {
			return 0;
		}
	}

	return 1;
}

char *run_sort_test(int (*func)(DArray *, DArray_compare), const char *name)
{
	DArray *words = create_words();
	mu_assert(!is_sorted(words), "Words should start not sorted.");
	
	debug("--- Testing %s sorting algorithm", name);
	int rc = func(words, (DArray_compare)testcmp);
	mu_assert(rc == 0, "sort failed");
	mu_assert(is_sorted(words), "didn't sort it");

	DArray_destroy(words);

	return NULL;
}

char *test_qsort()
{
	return run_sort_test(DArray_qsort, "qsort");
}

char *test_heapsort()
{
	return run_sort_test(DArray_heapsort, "heapsort");
}

char *test_mergesort()
{
	return run_sort_test(DArray_mergesort, "mergesort");
}

char *test_sort_add()
{
	DArray *words = create_words();
	DArray_qsort(words, (DArray_compare)testcmp);
	char *words2[] = {"twiggy", "pwnod", "asd13234", "kukareku", "9_("};
	int i = 0;

	for(i = 0; i < 5; i++) {
		DArray_sort_add(words, words2[i], (DArray_compare)testcmp);
		mu_assert(is_sorted(words), "Words should be sorted.");
	}

	DArray_destroy(words);

	return NULL;
}

char *test_find()
{
	DArray *words = create_words();
	DArray_qsort(words, (DArray_compare)testcmp);
	
	int res = DArray_find(words, "werwar", (DArray_compare)strcmp);
	mu_assert(res == 3, "Element is not there, but should be.");

	res = DArray_find(words, "wasderwar", (DArray_compare)strcmp);
	mu_assert(res == -1, "Element is there, but shouldn't be.");

	DArray_destroy(words);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_qsort);
	mu_run_test(test_heapsort);
	mu_run_test(test_mergesort);
	mu_run_test(test_sort_add);
	mu_run_test(test_find);

	return NULL;
}

RUN_TESTS(all_tests);
