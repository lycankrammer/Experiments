/*********************************************
 *                                           *
 *       C Header File: except.h             *
 *                                           *
 *********************************************/
#ifndef EXCEPT_INCLUDED
#define EXCEPT_INCLUDED
#include <setjmp.h>

#include <stddef.h>

#ifndef nullptr
typedef void* __nullptr_t;
#define nullptr ((__nullptr_t)+0)
#endif

/**********************************************
 * Exception handlers manipulate the adresses *
 * of exceptions. Exceptions must be global   *
 * static variables so that their adresses    *
 * identify them uniquely. It is an unchecked *
 * runtime error to declare an exception as a *
 * local variable or as a parameter.          *
 **********************************************/ 
#define T Except_T
typedef struct T {
	 const char *reason; /** this string is printed when an unhandled */
} T;                     /** exception occurs.                        */

/******************
 * EXPORTED TYPES *
 ******************/
typedef struct Except_Frame Except_Frame;
struct Except_Frame {
	Except_Frame *prev;
	jmp_buf env;
	const char *file;   /** file and line variables are exception  */
	unsigned long line; /** coordinates                            */
	const T *exception;
};

enum { Except_entered=0, Except_raised,
	   Except_handled, Except_finalized };
	   
/**********************
 * EXPORTED VARIABLES *
 **********************/
extern Except_Frame *Except_stack;
extern const Except_T Assert_Failed;

/**********************
 * EXPORTED FUNCTIONS *
 **********************/
void Except_raise(const T e[static 1], const char *file, unsigned long line);

/*******************
 * EXPORTED MACROS *
 *******************/
#define RAISE(e) Except_raise(&(e), __FILE__, __LINE__+0UL)
#define RERAISE Except_raise(Except_frame.exception, \
                 Except_frame.file, Except_frame.line)
#define RETURN switch (Except_stack = Except_stack->prev, 0) default: return

/*****************************************
 * automatic variables that are changed  *
 * in the body of TRY-EXCEPT must be     *
 * declared volatile                     *
 *****************************************/ 	 
#define TRY do {                                    \
	volatile int Except_flag;                       \
	Except_Frame Except_frame;                      \
	Except_frame.prev = Except_stack;               \
	Except_stack = &Except_frame;                   \
	Except_flag = setjmp(Except_frame.env);         \
	if (Except_flag == Except_entered) {

#define EXCEPT(e)                                   \
	if (Except_flag == Except_entered)              \
		Except_stack = Except_stack->prev;          \
	} else if (Except_frame.exception == &(e)) {    \
		Except_flag = Except_handled;                                

#define ELSE                                        \
	if (Except_flag == Except_entered)              \
		Except_stack = Except_stack->prev;          \
	} else {                                        \
		Except_flag = Except_handled; 

/** a FINALLY can be used for clean up, for example. */
#define FINALLY                                     \
	if (Except_flag == Except_entered)              \
		Except_stack = Except_stack->prev;          \
	} {                                             \
		if (Except_flag == Except_entered)          \
			Except_flag = Except_finalized; 

#define END_TRY                                     \
	if (Except_flag == Except_entered)              \
		Except_stack = Except_stack->prev;          \
	} if (Except_flag == Except_raised) RERAISE;    \
} while (0)

#undef T
#endif
