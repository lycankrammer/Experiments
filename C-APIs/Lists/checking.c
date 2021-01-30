/*********************************************
 *                                           *
 *             C file: checking.c            *
 *                                           *
 *********************************************/
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "except.h"

#include "memory.h"

/** For debugging purposes caused by trying access
 * some block of uninitialized memory.
 */
#define DEBUG_MEM_GARBAGE 0xA3

const Except_T Mem_Failed = { "Allocation Failed" };

/** This alignment ensures that any type of  data
 * can  be  stored  in  the  blocks  returned  by
 * mem_alloc. If the ptr passed to mem_free isn't
 * so aligned, it  can't  possibly be in htab and
 * is thus invalid.
 */
union align {
	int i;
	long l;
	long *lp;
	void *p;
	void (*fp)(void);
	float f;
	double d;
	long double ld;
};

#define NDESCRIPTORS 512
#define NALLOC ((4096 + sizeof(union align) - 1) / (sizeof(union align))) * (sizeof(union align))

#define hash(p, t) (((unsigned long)(p)>>3) & (sizeof(t)/sizeof((t)[0])-1))


/** The head of freelist is a  dummy descriptor and
 * the list  is threaded through the free fields of
 * the descriptors. This list is circular: freelist
 * is the last descriptor on the  list and its free
 * field points  to the first descriptor. At any gi_
 * ven time, htab holds descriptors  for all of the
 * blocks, both  free and allocated,  and  the free
 * blocks are  on freelist. Thus,  the descriptor's
 * free field is null if the block is allocated and
 * nonnull if it's free.
 */
static struct descriptor {
	struct descriptor *free;
	struct descriptor *link;
	const void *ptr;          //* adress of the block
	long size;
	const char *file;
	int line;
} *htab[2048];

static struct descriptor freelist = { &freelist };


static struct descriptor *find(const void *ptr)
{
	struct descriptor *bp = htab[hash(ptr, htab)];
	
	while (bp && bp->ptr != ptr) {
		bp = bp->link;
	}
	return bp;
}

static struct descriptor *dalloc(void *ptr, long size, const char *file, int line)
{
	static struct descriptor *avail;
	static int nleft;            // initialized to zero in first encounter during runtime
	
	if (nleft <= 0) {
		avail = malloc(NDESCRIPTORS * sizeof(*avail));
		if (!avail) return nullptr;
		nleft = NDESCRIPTORS;
	}
	*avail = (struct descriptor){ .ptr = ptr,
		                          .size = size,
		                          .file = file,
		                          .line = line,
		                          .free = nullptr,
		                          .link = nullptr
							  };					
	--nleft;
	return avail++;
}
		

/*******************************
 *        mem_alloc            *
 *******************************/
void *mem_alloc(long nbytes, const char *file, int line)
{
	//* This allocation method uses first-fit algorithm
	struct descriptor *bp, *prev;
	void *ptr;
	
	assert(nbytes > 0);
	//* round nbytes up to an alignment boundary
	nbytes = ((nbytes + sizeof(union align) - 1) / (sizeof(union align))) * (sizeof(union align));
	for (prev = &freelist, bp = freelist.free; bp; prev = bp, bp = bp->free) {
		if (bp->size > nbytes) {
			//* remove bp from freelist
			prev->free = bp->free;
			bp->free = nullptr;
			//* use the end of the block at bp->ptr
			bp->size -= nbytes;
			ptr = (char *) bp->ptr + bp->size;
			if ((bp = dalloc(ptr, nbytes, file, line))) {
				unsigned h = hash(ptr, htab);
				bp->link = htab[h];
				htab[h] = bp;
				/***********************************/
				#ifdef DEBUG
					memset(ptr, DEBUG_MEM_GARBAGE, nbytes);
				#endif
				/***********************************/					
				return ptr;
			}
			else {
				if (!file) RAISE(Mem_Failed);
				else Except_raise(&Mem_Failed, file, line);
			}
		}
		if (bp == &freelist) {
			struct descriptor *newptr;
			//* newptr = a block of size NALLOC + nbytes
			if (!(ptr = malloc(nbytes+NALLOC))
			|| !(newptr = dalloc(ptr, nbytes+NALLOC, __FILE__, __LINE__))) {
				if (!file) RAISE(Mem_Failed);
				else Except_raise(&Mem_Failed, file, line);
			}
			newptr->free = freelist.free;
			freelist.free = newptr;
		}
	}
	assert(0);
	return nullptr;
}

/*******************************
 *        mem_calloc           *
 *******************************/
void *mem_calloc(long count, long nbytes, const char *file, int line)
{
	void *ptr;
	
	assert(count > 0);
	assert(nbytes > 0);
	ptr = mem_alloc(count * nbytes, file, line);
	memset(ptr, '\0', count * nbytes);
	return ptr;
}
	
/*******************************
 *         mem_free            *
 *******************************/
void mem_free(void *ptr, const char *file, int line)
{
	if (ptr) {
		struct descriptor *bp;
		//* Raise exception if ptr is not valid, i.e.,
		//* do not point to an allocated block.
		//* The first test avoids calls to 'find' for
		//* those addresses  that aren't multiples of
		//* the strictest  alignment  and thus cannot
		//* possibly be valid block pointers.
		if (((unsigned long) ptr) % (sizeof(union align)) != 0
		|| !(bp = find(ptr)) || bp->free)
			Except_raise(&Assert_Failed, file, line);
		
		bp->free = freelist.free;
		freelist.free = bp;
	}
}
			
/*******************************
 *        mem_resize           *
 *******************************/
void *mem_resize(void *ptr, long nbytes, const char *file, int line)
{
	struct descriptor *bp;
		
	assert(ptr);
	assert(nbytes > 0);
	if (((unsigned long) ptr) % (sizeof(union align)) != 0  // see mem_free
	|| !(bp = find(ptr)) || bp->free)
		Except_raise(&Assert_Failed, file, line);

	void *newptr = mem_alloc(nbytes, file, line);
	memcpy(newptr, ptr, (nbytes < bp->size) ? nbytes : bp->size);
	mem_free(ptr, file, line);
	return newptr;
}
