#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <assert.h>

List *List_create()
{
	return calloc(1, sizeof(List));
}

void List_check(List *list)
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
	List_check(list);
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
	List_check(list);
	LIST_FOREACH(list, first, next, cur) {
		//printf("ptr: %p\n", cur->value);
		free(cur->value);
	}
}

void List_clear_destroy(List *list)
{
	List_check(list);
	LIST_FOREACH(list, first, next, cur) {
		//printf("Freeing val %s %p\n", cur->value, cur->value);
		free(cur->value);
		if(cur->prev) {
			//printf("Freeing prev: %p\n", cur->prev);
			free(cur->prev);
		}		
	}

	//printf("Freeing last: %p\n", list->last);
	free(list->last);
	//printf("Freeing list: %p\n", list);
	free(list);
}

void List_push(List *list, void *value)
{
	List_check(list);
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
	List_check(list);
	ListNode *node = list->last;
	return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
	List_check(list);
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
	List_check(list);
	ListNode *node = list->first;
	return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
	List_check(list);
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

List *List_copy(List *list)
{
	List_check(list);
	List *res = List_create();
	LIST_FOREACH(list, first, next, cur) {
		List_push(res, strdup(cur->value));
	}

	return res;	
}

List *List_join(List *list1, List *list2)
{
	List_check(list1);
	List_check(list2);
	List *res = NULL;

	if(list1->first == NULL) {
		res = List_copy(list2);
	} else {
		res = List_copy(list1);
		LIST_FOREACH(list2, first, next, cur) {
			List_push(res, strdup(cur->value));
		}
	}
	
	return res;
}

int List_split(List *list1, List *list2, void *value, List_compare fn)
{
	List_check(list1);
	List_check(list2);
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
		printf("%s ", (char *)cur->value);
	}
	printf("\n");
}

/*int main(int argc, char *argv[])
{
	List *a = List_create();
	//List *b = List_create();
	char *test1 = strdup("abc");
	List_push(a, test1);
	List_push(a, strdup("def"));
	List_push(b, "ghi");
	List *c = List_copy(a, b);
	List_print(c, "c");
	List_clear_destroy(c);
	List_destroy(a);
	List_destroy(b);
	List_print(a, "a");
	List_clear_destroy(a);

	return 0;
}*/
