/*********************************************
 *                                           *
 *           C file: arena.c                 *
 *                                           *
 *********************************************/
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "except.h"
#include "arena.h"

/** The arena structure  heads a linked list  of chunks in
 ** which the links are the 'prev' fields in copies of the
 ** arena structures that begin each chunk.
 **/

#define T Arena_T

const Except_T Arena_NewFailed = { "Arena Creation Failed" };
const Except_T Arena_Failed = { "Arena Allocation Failed" };

/**************
 * macros     *
 **************/
#define THRESHOLD 10

/**************
 * types      *
 **************/
union align {   //** The size of this union gives the minimum
	int i;      //** alignment on the host machine. 
	long l;
	long *lp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
}; 
 
struct T {       //* an  arena  describes  a  chunk of  memory
	T prev;      //* points   to   the   head   of  the  chunk  
	char *avail; //* points to the chunk's first free location
	char *limit; //* points  just  pass the  end  of the chunk
};

union header {
	struct T b;
	union align a;
};

/**************
 * data       *
 **************/
static T freechunks;
static long nfree;

/**************
 * functions  *
 **************/

/*******************************
 *         Arena_new           *
 *******************************/
T Arena_new(void)
{
	T arena = malloc(sizeof(*arena));
	
	if (!arena)
		RAISE(Arena_NewFailed);
		
	arena->prev = nullptr;
	arena->limit = arena->avail = nullptr;
	return arena;
}	

/*******************************
 *       Arena_dispose         *
 *******************************/
void Arena_dispose(T *ap)
{
	assert(ap && *ap);
	
	Arena_free(*ap);
	free(*ap);
	*ap = nullptr;
}

/*******************************
 *       Arena_alloc           *
 *******************************/
void *Arena_alloc(T arena, long nbytes, const char *file, int64_t line)
{
	/** Most allocations round the request amount up to the
	 ** proper  alignment boundary, increment  the  'avail'
	 ** pointer by the  amount of  the rounded request, and
	 ** return the previous value. **/
	assert(arena);
	assert(nbytes > 0);
	
	/** round nbytes up to an alignment boundary **/
	nbytes = ((nbytes + sizeof(union align) - 1) / (sizeof(union align))) * (sizeof(union align));
	while (nbytes > arena->limit - arena->avail) {
		/** get a new chunk **/
		T ptr;
		char *limit;
		/** get a new chunk **/
		if ((ptr = freechunks)) {
			freechunks = freechunks->prev;
			--nfree;
			limit = ptr->limit;
		}
		else {
			/** size of arena structure + nbytes + 10k bytes **/
			long m = sizeof(union header) + nbytes + 10*1024; 
			ptr = malloc(m);
			if (!ptr) {
				if (!file)
					RAISE(Arena_Failed);
				else
					Except_raise(&Arena_Failed, file, line);
			}
			limit = (char *) ptr + m;
		}
		*ptr = *arena;  //* pushes *arena by saving it at the beginning of the new chunk
		arena->avail = (char *)((union header *) ptr + 1);
		arena->limit = limit;
		arena->prev = ptr;	
	}
	arena->avail += nbytes;
	return arena->avail - nbytes;
}
	 
/*******************************
 *      Arena_calloc           *
 *******************************/
void *Arena_calloc(T arena, long count, long nbytes, const char *file, int64_t line)
{
	assert(count > 0);
	
	void *ptr = Arena_alloc(arena, count * nbytes, file, line);
	memset(ptr, '\0', count * nbytes);
	return ptr;
}

/*******************************
 *        Arena_free           *
 *******************************/
void Arena_free(T arena)
{
	/** An arena is deallocated by adding its chunks to the
	 ** list of free chunks, which  also restores *arena to
	 ** its initial state as the list is traversed. **/
	assert(arena);
	
	while (arena->prev) {
		/** This assignment copies  to 'tmp'  all of  the fields
		 ** of the arena structure  pointed to by 'arena->prev'.
		 ** This assignment and '*arena = tmp;' "pops" the stack
		 ** of arena structures formed by the list of chunks. **/
		struct T tmp = *arena->prev;  
		/** free the chunk described by arena **/
		if (nfree < THRESHOLD) {
			arena->prev->prev = freechunks;
			freechunks = arena->prev;
			++nfree;
			freechunks->limit = arena->limit;
		}
		else {  //* (nfree >= THRESHOLD) To avoid tying up too much storage
			/** Once nfree reaches THRESHOLD, subsequent chunks are
			 ** deallocated by calling free. **/
			 free(arena->prev);
		 }
		*arena = tmp;
	}
	assert(arena->limit == nullptr);
	assert(arena->avail == nullptr);
}
