/*****************************************
 *                                       *
 *         C file: production.c          *
 *                                       *
 *****************************************/
#include <stdlib.h>
#include <stddef.h>

#include "assert.h"
#include "except.h"

#include "memory.h"

const Except_T Mem_Failed = { "Allocation Failed" };

/*****************************
 *       mem_alloc           *
 *****************************/
void *mem_alloc(long nbytes, const char *file, int line)
{
	void *ptr;
	
	assert(nbytes > 0);
	ptr = malloc(nbytes);
	if (!ptr) {
		if (!file) RAISE(Mem_Failed);
		else Except_raise(&Mem_Failed, file, line);
	}
	return ptr;
}

/*******************************
 *        mem_calloc           *
 *******************************/
void *mem_calloc(long count, long nbytes, const char *file, int line)
{
	void *ptr;
	
	assert(count > 0);
	assert(nbytes > 0);
	ptr = calloc(count, nbytes);
	if (!ptr) {
		if (!file) RAISE(Mem_Failed);
		else Except_raise(&Mem_Failed, file, line);
	}
	return ptr;
}

/*******************************
 *         mem_free            *
 *******************************/
void mem_free(void *ptr, const char *file, int line)
{
	//* The standard permits null pointers to be passed
	//* to free, but mem_free doesn't pass them, because
	//* old implementations of free may not accept null
	//* pointers.
	if (ptr) free(ptr);
}

/*******************************
 *        mem_resize           *
 *******************************/
void *mem_resize(void *ptr, long nbytes, const char *file, int line)
{
	assert(ptr);
	assert(nbytes > 0);
	ptr = realloc(ptr, nbytes);
	if (!ptr) {
		if (!file) RAISE(Mem_Failed);
		else Except_raise(&Mem_Failed, file, line);
	}
	return ptr;
}
