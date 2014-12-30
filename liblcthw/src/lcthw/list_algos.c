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
				}
				swapped = 1;
			}
		}
	}
	return 0;
}

int List_merge_sort(List *list, List_compare fn)
{
	return 0;
}
