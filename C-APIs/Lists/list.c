/********************************************
*                                           *
*            C file: list.c                 *
*                                           *
********************************************/
#include <stdarg.h>
#include <stddef.h>

#include "assert.h"
#include "memory.h"
#include "list.h"

#define T List_T


/*****************************
*         List_push          *
*****************************/
T List_push(T list, void *x)
{
	T p;
	
	NEW(p);
	p->first = x;
	p->rest = list;
	return p;
}

/*****************************
*         List_list          *
*****************************/
T List_list(void *x, ...)
{
	va_list ap;
	T list, *p = &list;
	
	va_start(ap, x);
	for (; x; x = va_arg(ap, void *)) {
		NEW(*p);
		(*p)->first = x;
		p = &(*p)->rest;
	}
	*p = nullptr;
	va_end(ap);
	return list;
}
	
/*****************************
*        List_append         *
*****************************/	
T List_append(T list, T tail)  // Change to constant time (hide struct T)
{
	T *p = &list;
	
	while (*p)
		p = &(*p)->rest;
	*p = tail;
	return list;
}	
	
/*****************************
*        List_copy           *
*****************************/
T List_copy(T list)
{
	T head, *p = &head;
	
	for (; list; list = list->rest) {
		NEW(*p);
		(*p)->first = list->first;
		p = &(*p)->rest;
	}
	*p = nullptr;
	return head;
}

/*****************************
*        List_pop            *
*****************************/
T List_pop(T list, void **x)
{
	if (list) {
		T head = list->rest;
		if (x) *x = list->first;
		FREE(list);
		return head;
	}
	else {
		return list;
	}
}
		
/*****************************
*       List_reverse         *
*****************************/
T List_reverse(T list)
{
	T head = nullptr, next;
	
	for (; list; list = next) {
		next = list->rest;
		list->rest = head;
		head = list;
	}
	return head;
}

/*****************************
*       List_length          *
*****************************/
size_t List_length(T list)
{
	size_t n;
	
	for (n = 0; list; list = list->rest)
		++n;
	return n;
}

/*****************************
*        List_free           *
*****************************/
void List_free(T *list)
{
	T next;
	
	assert(list);
	for (; *list; *list = next) {
		next = (*list)->rest;
		FREE(*list);
	}
}

/*****************************
*         List_map           *
*****************************/
void List_map(T list, void (*apply)(void **x, void *cl), void *cl)
{
	assert(apply);
	
	for (; list; list = list->rest) {
		apply(&list->first, cl);
	}
}

/*****************************
*      List_to_array         *
*****************************/
void **List_to_array(T list, void *end)
{
	size_t n = List_length(list);
	void **array = ALLOC((n+1) * sizeof(*array));
	
	size_t i;
	for (i = 0; i < n; i++) {
		array[i] = list->first;
		list = list->rest;
	}
	array[i] = end;
	return array;
}
