#include <lcthw/list_algos.h>
#include <assert.h>

int List_bubble_sort(List *list, List_compare fn)
{	
	int swapped = 1;
	int count = List_count(list);
	int i;
	int skip;
	ListNode *cur;
	char *tmp; 
	while(swapped == 1) {
		swapped = 0;
		skip = 0;
		cur = list->first;
		i = count;
		while(i > 0) {
			if(cur != list->last) {
				if(fn(cur->value, cur->next->value) > 0) {
					// swap 2 elemets
					tmp = cur->value;
					cur->value = cur->next->value;
					cur->next->value = tmp;
					swapped = 1;
					skip = List_count(list) - i;
				}
				cur = cur->next;
			}
			i--;
		}
		count = skip;
	}
	return 0;
}

/*List *List_merge(List *list1, List *list2, List_compare fn)
{
	List_check(list1);
	List_check(list2);

	List *res = List_create();
	
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

	return res;
}*/

inline List* List_merge(List *left, List *right, List_compare cmp)
{
	List_check(left);
	List_check(right);

	List *result = List_create();
	void *val = NULL;

	/*if(cmp(left->last->value, right->first->value) < 0) {
		List_join(left, right, result);
		return result;
	}*/

	while(List_count(left) > 0 || List_count(right) > 0) {
		if(List_count(left) > 0 && List_count(right) > 0) {
			if(cmp(List_first(left), List_first(right)) <= 0) {
				val = List_shift(left);			
			} else {
				val = List_shift(right);
			}

			List_push(result, val);
		} else if(List_count(left) > 0) {
			val = List_shift(left);
			List_push(result, val);
		} else if(List_count(right) > 0) {
			val = List_shift(right);
			List_push(result, val);
		}
	}

	return result;
}

List *List_merge_sort(List *list, List_compare fn)
{	
	List_check(list);
	if(List_count(list) < 2) {
		return list;
	}

	List *a = List_create();
	List *b = List_create();
	List_split(list, a, b);
	List *res = List_merge(List_merge_sort(a, fn), List_merge_sort(b, fn), fn);
	List_clear_destroy(a);
	List_clear_destroy(b);

	return res;
}

/*List *List_merge_sort(List *list, List_compare cmp)
{
	if(List_count(list) <= 1) {
		return list;
	}

	List *left = List_create();
	void *val = NULL;
	//List *right = List_create();
	int middle = List_count(list) / 2;

	LIST_FOREACH(list, first, next, cur) {
		if(middle > 0) {
			val = List_shift(list);
			List_push(left, val);
		}// else {
			//List_push(right, cur->value);
		//}

		middle--;
	}

	List *sort_left = List_merge_sort(left, cmp);
	//List *sort_right = List_merge_sort(right, cmp);
	List *sort_right = List_merge_sort(list, cmp);

	if(sort_left != left) List_destroy(left);
	//if(sort_right != right) List_destroy(right);

	return List_merge(sort_left, sort_right, cmp);
}*/

int List_insert_sorted(List *list, void* value, List_compare fn)
{
	List_check(list);
	ListNode *before;

	LIST_FOREACH(list, first, next, cur) {
		if(cur->next != NULL) {
			if((fn(cur->value, value) <= 0) && (fn(cur->next->value, value) > 0)) {
				before = cur;
				break;
			}
		}
	}

	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;
	node->prev = before;
	node->next = before->next;
	before->next->prev = node;
	before->next = node;
	return 0;

error:
	return -1;
}
