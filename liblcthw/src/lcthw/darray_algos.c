#include <lcthw/darray_algos.h>
#include <stdlib.h>
#include <bsd/stdlib.h>

int DArray_qsort(DArray *array, DArray_compare cmp)
{
	qsort(array->contents, DArray_count(array), sizeof(void *), cmp);
	return 0;
}

int DArray_heapsort(DArray *array, DArray_compare cmp)
{
	return heapsort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_mergesort(DArray *array, DArray_compare cmp)
{
	return mergesort(array->contents, DArray_count(array), sizeof(void *), cmp);
}

int DArray_sort_add(DArray *array, void *el, DArray_compare cmp) 
{
	DArray_push(array, el);
	DArray_qsort(array, cmp);
	return 0;
}

int DArray_find(DArray *array, void *el, DArray_compare cmp)
{
	int low = 0;
	int high = array->end - 1;

	while (low <= high) {
		int middle = low + (high - low)/2;
		void *key = array->contents[middle];

		if (cmp(el, key) < 0) {
			high = middle - 1;
		} else if (cmp(el, key) > 0) {
			low = middle + 1;
		} else {
			return middle;
		}
	}

	return -1;

}
