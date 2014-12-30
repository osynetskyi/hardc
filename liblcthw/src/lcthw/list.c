#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>

List *List_create()
{
	return calloc(1, sizeof(List));
}

void check_list(List *list)
{
	assert(list != NULL);
	assert(list->count >= 0);
	if(list->count > 0) {
		assert(list->first != NULL);
		assert(list->last != NULL);
	}
	if(list->first == NULL) {
		assert(list->last == NULL);
		assert(list->count == 0);
	}
	if(list->last == NULL) {
		assert(list->first == NULL);
		assert(list->count == 0);
	}
}

void List_destroy(List *list)
{
	check_list(list);
	LIST_FOREACH(list, first, next, cur) {
		if(cur->prev) {
			free(cur->prev);
		}
	}

	free(list->last);
	free(list);
}

void List_clear(List *list)
{
	check_list(list);
	LIST_FOREACH(list, first, next, cur) {
		free(cur->value);
	}
}

void List_clear_destroy(List *list)
{
	check_list(list);
	LIST_FOREACH(list, first, next, cur) {
		if(cur->prev) {
			free(cur->prev);
		}		
		free(cur->value);
	}
}

void List_push(List *list, void *value)
{
	check_list(list);
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;

	if(list->last== NULL){
		list->first = node;
		list->last = node;
	} else {
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}

	list->count++;

error:
	return;
}

void *List_pop(List *list)
{
	check_list(list);
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
	check_list(list);
	ListNode *node = calloc(1, sizeof(ListNode));
	check_mem(node);

	node->value = value;
	
	if(list->first == NULL) {
		list->first = node;
		list->last = node;
	} else {
		node->next = list->first;
		list->first->prev = node;
		list->first = node;
	}

	list->count++;

error:
	return;
}

void *List_shift(List *list)
{
	check_list(list);
	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	check_list(list);
	void *result = NULL;

	check(list->first && list->last, "List is empty.");
	check(node, "node can't be NULL.");

	if(node == list->first && node == list->last) {
		list->first = NULL;
		list->last = NULL;
	} else if(node == list->first) {
		list->first = node->next;
		check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
		list->first->prev = NULL;
	} else if(node == list->last) {
		list->last = node->prev;
		check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
		list->last->next = NULL;
	} else {
		ListNode *after = node->next;
		ListNode *before = node->prev;
		after->prev = before;
		before->next = after;
	}

	list->count--;
	result = node->value;
	free(node);

error:
	return result; 
}

void List_copy(List *list1, List *list2)
{
	check_list(list1);
	//check_list(list2);
	LIST_FOREACH(list1, first, next, cur) {
		List_push(list2, cur->value);
	}
	
}

void List_join(List *list1, List *list2)
{
	check_list(list1);
	check_list(list2);
	if((list1->first == NULL)&&(list2->first != NULL)) {
		List_join(list2, list1);		
	} else if(list2->first != NULL) {
		list1->last->next = list2->first;
		list2->first->prev = list1->last;
		list1->last = list2->last;
		list1->count += list2->count;	
	}
}

int List_split(List *list1, List *list2, void *value, compare fn)
{
	check_list(list1);
	check_list(list2);
	int k = list1->count;
	int n = 0;
	ListNode *oldlast = list1->last;
	LIST_FOREACH(list1, first, next, cur) {
		if(fn(cur->value, value) == 0) {
			list1->last = cur->prev;
			list1->last->next = NULL;
			list2->first = cur;
			list2->first->prev = NULL;
			list2->last = oldlast;
			list1->count = n;
			list2->count = k - n;
			return 0;
		} else {
			n++;
		}
	}

	return -1;
}

void List_print(List *list, char *banner)
{
	printf("%s: ", banner);
	LIST_FOREACH(list, first, next, cur) {
		printf("%s ", cur->value);
	}
	printf("\n");
}
