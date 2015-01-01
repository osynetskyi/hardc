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

int List_merge(List *list1, List *list2, List *res)
{
	List_check(list1);
	List_check(list2);
	List_check(res);
	
	ListNode *a = list1->first;
	ListNode *b = list2->first;

	while((a != NULL)&&(b != NULL)) {
		if(a->value <= b->value) {
			List_push(res, a->value);
			a = a->next;
		} else {
			List_push(res, b->value);
			b = b->next;
		}
	}

	/*if((a == NULL) && (b != NULL)) {
		LIST_FOREACH(list2, b, next, cur) {
			List_push(res, cur->value);
		}
	} else if((a != NULL) && (b == NULL)) {
		LIST_FOREACH(list1, a, next, cur) {
			List_push(res, cur->value);
		}
	}*/
	
	return 0;
}

int List_merge_sort(List *list, List_compare fn)
{
	return 0;
}
