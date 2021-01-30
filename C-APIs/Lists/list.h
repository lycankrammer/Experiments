/**********************************************
*                                             *
*         C Header file: list.h               *
*                                             *
**********************************************/
#ifndef LIST_HDR
#define LIST_HDR 1

#include "nullptr.h"
#include <inttypes.h>

#define T List_T
typedef struct T *T;

struct T {
	T rest;
	void *first;
};


/**********************************
*      Public interfaces          *
**********************************/
extern T List_append(T list, T tail);
extern T List_copy(T list);
extern T List_list(void *x, ...);
extern T List_pop(T list, void **x);
extern T List_push(T list, void *x);
extern T List_reverse(T list);
extern size_t List_length(T list);
extern void List_free(T *list);
extern void List_map(T list, void (*apply)(void **x, void *cl), void *cl);
extern void **List_to_array(T list, void *end);

#undef T
#endif
