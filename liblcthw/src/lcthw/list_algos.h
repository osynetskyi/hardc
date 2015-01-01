#ifndef lcthw_List_algos_h
#define lcthw_List_algos_h

#include <lcthw/list.h>
#include <lcthw/dbg.h>
#include <stdlib.h>

int List_bubble_sort(List *list, List_compare fn);

int List_merge_sort(List *list, List_compare fn);

#endif
