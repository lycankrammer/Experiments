/*********************************************
 *                                           *
 *          C File: except.c                 *
 *                                           *
 *********************************************/
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "except.h"

#define T Except_T

Except_Frame *Except_stack = nullptr;

/**********************************
 *      Except_raise              *
 **********************************/
void Except_raise(const T e[static 1], const char *file, unsigned long line)
{
	Except_Frame *p = Except_stack;
	
	assert(e);
	if (!p) { /** announce an uncaught exception */
		fprintf(stderr, "Uncaught exception");
		if (e->reason)
			fprintf(stderr, " %s", e->reason);
		else
			fprintf(stderr, " at 0x%p", e);
		if (file && line > 0)
			fprintf(stderr, " raised at %s:%d\n", file, line);
		fprintf(stderr, "aborting...\n");
		fflush(stderr);
		abort();	
	}
	p->exception = e;
	p->file = file;
	p->line = line;
	Except_stack = Except_stack->prev;
	longjmp(p->env, Except_raised);
}
/** EOF */
