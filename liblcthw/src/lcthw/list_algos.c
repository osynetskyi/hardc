#include <lcthw/list_algos.h>
#include <assert.h>

int List_bubble_sort(List *list, List_compare fn)
{	
	int swapped = 1;
	ListNode *cur;
	char *tmp; 
	while(swapped == 1) {
		swapped = 0;
		cur = list->first;
		while(cur != list->last) {
			if(fn(cur->value, cur->next->value) > 0) {
				// swap 2 elemets
				tmp = cur->value;
				cur->value = cur->next->value;
				cur->next->value = tmp;
				swapped = 1;
			}
			cur = cur->next;
		}
	}
	return 0;
}

int List_merge(List *list1, List *list2, List *res, List_compare fn)
{
	List_check(list1);
	List_check(list2);
	List_check(res);
	List_destroy(res);
	res = List_create();
	
	ListNode *a = list1->first;
	ListNode *b = list2->first;

	while((a != NULL)&&(b != NULL)) {
		if(fn(a->value, b->value) <= 0) {
			List_push(res, strdup(a->value));
			a = a->next;
		} else {
			List_push(res, strdup(b->value));
			b = b->next;
		}
	}

	if((a == NULL) && (b != NULL)) {
		while(b != NULL) {
			List_push(res, strdup(b->value));
			b = b->next;
		}
	} else if((a != NULL) && (b == NULL)) {
		while(a != NULL) {
			List_push(res, strdup(a->value));
			a = a->next;
		}
	}

	/*if(a) {
		if(a->value) {
			free(a->value);
		}
		free(a);
	}
	
	if(b) {
		if(b->value) {
			free(b->value);
		}
		free(b);
	}*/

	return 0;
}

List *List_merge_sort(List *list, List_compare fn)
{	
	List_check(list);
	List *res = List_create();
	List_copy(list, res);
	if(List_count(res) > 1) {
		List *a = List_create();
		List *b = List_create();
		List_split(res, a, b);
		a = List_merge_sort(a, fn);
		b = List_merge_sort(b, fn);
		List_merge(a, b, res, fn);
		List_clear_destroy(a);
		List_clear_destroy(b);
	}
	return res;
}
