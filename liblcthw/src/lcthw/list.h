#ifndef lcthw_List_h
#define lcthw_List_h

#include <stdlib.h>

// basic structure, list node
struct ListNode;

//ListNode contents
typedef struct ListNode {
	struct ListNode *prev;
	struct ListNode *next;
	void *value;
} ListNode;

// List is a container of ListNodes
typedef struct List {
	int count;
	ListNode *first;
	ListNode *last;
} List;

// comparison function for elements
typedef int (*List_compare) (void *a, void *b);

//create a list
List *List_create();

// check list for validity
void List_check(List *list);

//free memory from list structures
void List_destroy(List *list);

// erase list values
void List_clear(List *list);

// erase values & free memory
void List_clear_destroy(List *list);

// return the number of list elements
#define List_count(A) ((A)->count)

// return first element of the list
#define List_first(A) ((A)->first != NULL ? (A)->first->value : NULL)

// return last element of the list
#define List_last(A) ((A)->last != NULL ? (A)->last->value : NULL)

// add one element to the end of the list
void List_push(List *list, void *value);

// remove element from the end of the list
void *List_pop(List *list);

// add one element to the front of the list
void List_unshift(List *list, void *value);

// remove element from the front of the list
void *List_shift(List *list);

// remove a node from list
void *List_remove(List *list, ListNode *node);

// joins two lists together
List *List_join(List *list1, List *list2);

// copy first list to the second, and not just pointers
List *List_copy(List *list);//1, List *list2);

// split list on element
int List_split(List *list1, List *list2, void *value, List_compare fn);

// print list contents
void List_print(List *list, char *banner);

// cycle through list contents
#define LIST_FOREACH(L, S, M, V) ListNode *_node = NULL;\
	ListNode *V = NULL;\
	for(V = _node = L->S; _node != NULL; V = _node = _node->M)

#endif
