/*********************************************
 *                                           *
 *        C Header file: arena.h             *
 *                                           *
 *********************************************/
#ifndef ARENA_INCLUDED
#define ARENA_INCLUDED 1

#include <inttypes.h>

#include "except.h"
#include "nullptr.h"

/** The  files 'arena.h' and  'arena.c' describes
 * memory-management interface and implementation
 * that uses arena-based algorithms, which alloca_
 * te memory from an arena and deallocate  entire
 * arenas at once.
 */
 
#define T Arena_T
typedef struct T *T;

extern const Except_T Arena_NewFailed;
extern const Except_T Arena_Failed;

/************************
 * exported functions   *
 ************************/
extern T Arena_new(void);
extern void Arena_dispose(T *ap);
extern void *Arena_alloc(T arena, long nbytes, const char *file, int64_t line);
extern void *Arena_calloc(T arena, long count, long nbytes, const char *file, int64_t line);
extern void Arena_free(T arena);


#undef T
#endif
