#include "minunit.h"
#include <lcthw/darray.h>
#include <time.h>

static DArray *array = NULL;
static int *val1 = NULL;
static int *val2 = NULL;

char *test_create()
{
	array = DArray_create(sizeof(int), 100);
	mu_assert(array != NULL, "DArray create failed.");
	mu_assert(array->contents != NULL, "contets are wrong in darray.");
	mu_assert(array->end == 0, "end isn't at the rigth spot");
	mu_assert(array->element_size == sizeof(int), "element size is wrong.");
	mu_assert(array->max == 100, "wrong max length on initial size");

	return NULL;
}

char *test_destroy()
{
	DArray_destroy(array);

	return NULL;
}

char *test_new()
{
	val1 = DArray_new(array);
	mu_assert(val1 != NULL, "failed to make a new element");
	*val1 = 101;

	val2 = DArray_new(array);
	mu_assert(val2 != NULL, "failed to make a new element");
	*val2 = 102;

	return NULL;
}

char *test_set()
{
	DArray_set(array, 0, val1);
	DArray_set(array, 1, val2);

	return NULL;
}

char *test_get()
{
	int *gotten = DArray_get(array, 0);
	mu_assert(DArray_get(array, 0) == val1, "Wrong first value.");
	mu_assert(DArray_get(array, 1) == val2, "Wrong second value.");
	mu_assert(*gotten == *val1, "Looks like our int is not here.");
	mu_assert(*((int *)DArray_get(array, 1)) == *val2, "Looks like our other int is not here.");

	return NULL;
}

char *test_remove()
{
	int *val_check = DArray_remove(array, 0);
	mu_assert(val_check != NULL, "Should not get NULL.");
	mu_assert(*val_check == *val1, "Should get the first value.");
	mu_assert(DArray_get(array, 0) == NULL, "Should be gone.");
	free(val_check);

	val_check = DArray_remove(array, 1);
	mu_assert(val_check != NULL, "Should not get NULL.");
	mu_assert(*val_check == *val2, "Should get the first value.");
	mu_assert(DArray_get(array, 1) == NULL, "Should be gone.");
	free(val_check);

	return NULL;
}

char *test_expand_contract()
{
	int old_max = 0;
	int experiments = 35;
	int i = 0;

	clock_t start = clock();
	for (i = 0; i < experiments; i++) {
		old_max = array->max;
		DArray_expand(array);
		mu_assert((unsigned int)array->max == old_max + array->expand_rate, "Wrong size after expand.");
	}

	for (i = 0; i < experiments; i++) {
		old_max = array->max;
		DArray_contract(array);
		mu_assert((unsigned int)array->max == array->expand_rate + 1, "Shoud stay at the expand_rate at least.");
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Expanding-contracting (+) %d times took %f sec\n", experiments, seconds);

	DArray_contract(array);
	mu_assert((unsigned int)array->max == array->expand_rate + 1, "Should stay at the expand_rate at least.");

	return NULL;
}

char *test_push_pop()
{
	int i = 0;
	int *test = NULL;
	for(i = 0; i < 1000; i++) {
		int *val = DArray_new(array);
		*val = i * 333;
		DArray_push(array, val);
	}

	for (i = 0; i < 1000; i++){
		test = DArray_get(array, i+1);
		mu_assert(*test == i * 333, "Wrong element after push.");
	}

	mu_assert(array->max == 1201, "Wrong max size.");

	for(i = 999; i >= 0; i--) {
		int *val = DArray_pop(array);
		mu_assert(val != NULL, "Shouldn't get a NULL.");
		mu_assert(*val == i * 333, "Wrong value.");
		DArray_free(val);
	}
	
	return NULL;
}

char *test_timing()
{
	int num = 10000000;
	int i = 0;
	clock_t start = clock();
	
	for(i = 0; i < num; i++) {
		int *val = DArray_new(array);
		*val = i * 33;
		DArray_push(array, val);
		val = DArray_pop(array);
		DArray_free(val);
	}

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Pushing and popping %d elements took %f sec\n", num, seconds);

	return NULL;
}

char *test_expand_contract_mult()
{
	int old_max = 0;
	double rate = 1.5;
	int experiments = 35;
	int i = 0;

	clock_t start = clock();
	for (i = 0; i < experiments; i++) {
		old_max = array->max;
		DArray_expand_mult(array, rate);
		mu_assert(array->max == (int)(old_max * rate), "Wrong max size after expand.");
	}

	for (i = 0; i < experiments; i++) {
		old_max = array->max;
		DArray_contract_mult(array, rate);
		mu_assert(array->max == (int)(old_max / rate) + 1, "Wrong max size after contract.");
	}
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("Expanding-contracting (*) %d times took %f sec\n", experiments, seconds);

	return NULL;
}

char *all_tests()
{
	mu_suite_start();

	mu_run_test(test_create);
	mu_run_test(test_new);
	mu_run_test(test_set);
	mu_run_test(test_get);
	mu_run_test(test_remove);
	mu_run_test(test_expand_contract);
	mu_run_test(test_push_pop);
	mu_run_test(test_timing);
	mu_run_test(test_expand_contract_mult);
	mu_run_test(test_destroy);

	return NULL;
}

RUN_TESTS(all_tests);
