/******************************************
 *                                        *
 *       C Header file: memory.h          *
 *                                        *
 ******************************************/
#ifndef MEMORY_INCLUDED
#define MEMORY_INCLUDED 1

#include "except.h"

/** THIS HEADER HAS TWO IMPLEMENTATIONS DEFINED BY
 * 'production.c' AND 'checking.c'. THE LATTER DOES
 * CHECKED RUNTIME ERRORS FOR ALLOCATION AND DEALLO_
 * CATION FUNCTIONS. ONLY ONE IMPLEMENTATION OF THIS
 * INTERFACE MAY BE USED IN ANY GIVEN PROGRAM.
 */

/*****************************************
 * 'memory.h's allocation functions are  *
 * similar to those in the standard C    *
 * library, but they don't accept zero   *
 * sizes and never return null pointers. *
 *****************************************/

/*****************************
 * exported exceptions       *
 *****************************/
extern const Except_T Mem_Failed;
/*****************************
 * exported functions        *
 *****************************/
extern void *mem_alloc(long nbytes, const char *file, int line);
extern void *mem_calloc(long count, long nbytes, const char *file, int line);
extern void mem_free(void *ptr, const char *file, int line);
extern void *mem_resize(void *ptr, long nbytes, const char *file, int line);
/*****************************
 * exported macros           *
 *****************************/
#define ALLOC(nbytes)         \
	mem_alloc((nbytes), __FILE__, __LINE__)
#define CALLOC(count, nbytes) \
	mem_calloc((count), (nbytes), __FILE__, __LINE__)
#define NEW(p) ((p) = ALLOC((long) sizeof *(p)))
#define NEWO(p) ((p) = CALLOC(1, (long) sizeof *(p)))
#define FREE(ptr) ((void)(mem_free((ptr), __FILE__, __LINE__), (ptr) = nullptr))
#define RESIZE(ptr, nbytes) ((ptr) = mem_resize((ptr), (nbytes), __FILE__, __LINE__))

#endif
