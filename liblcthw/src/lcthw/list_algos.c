#include <lcthw/list_algos.h>
#include <lcthw/dbg.h>
#include <assert.h>

int List_bubble_sort(List *list, List_compare fn)
{	
	int swapped = 1;
	while(swapped == 1) {
		swapped = 0;
		LIST_FOREACH(list, first, next, cur) {
			if((cur != list->last)&&(fn(cur->value, cur->next->value) > 0)) {
				// swap 2 elemets
				if(cur->prev == NULL) { 			// if we need to move first
					list->first = cur->next;
					cur->prev = list->first;
					cur->next = list->first->next;
					list->first->next->prev = cur;
					list->first->prev = NULL;
				} else if(cur->next == NULL) { 		// if we need to move last
					cur->next->prev = cur->prev;
					cur->next->next = cur;
					cur->prev = cur->next;
					cur->next = NULL;
					list->last = cur;
				} else { 							// other cases
					cur->prev->next = cur->next;
					cur->next->prev = cur->prev;
					cur->next = cur->prev;
					cur->prev = cur->prev->prev;
					cur->next->next->prev = cur;
					//cur->next->next = cur;
				}
				swapped = 1;
			}
		}
	}

	List_print(list, "sorted");
	return 0;
}

/*List *merge(List *list1, List *list2)
{
	List_check(list1);
	List_check(list2);
	static List *res = List_create();
	
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

	if((a == NULL) && (b != NULL)) {
		LIST_FOREACH(list2, b, next, cur) {
			List_push(res, cur->value);
		}
	} else if((a != NULL) && (b == NULL)) {
		LIST_FOREACH(list1, a, next, cur) {
			List_push(res, cur->value);
		}
	}
	
	return res;
}*/

/*int List_halfsplit(List *list1, List *list2)
{
	int n = List_count(list1);
	int middle = n / 2;
	
	return 0;
}*/

int List_merge_sort(List *list, List_compare fn)
{
	return 0;
}
