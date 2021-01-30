/**********************************************
 *                                            *
 *        C Header File: assert.h             *
 *                                            *
 **********************************************/

/** This interface defines assert(e) as specified by
 * the standard, except that an assertion failure raises
 * the exception Assert_Failed instead of aborting execution,
 * and does not provide the text of the assertion e.
 * Assert mimics the standard's definitions so that the two
 * assert.h headers can be used interchangeably.
 * 
 * e1 || e2 <=> if (!(e1)) e2; when alone as a statement.
 * The definition of assert uses e1||e2 because assert(e)
 * must expand into an expression, not a statement. e2 is
 * a comma expression whose result is a value, which is
 * required by ||, and the entire expression is cast to
 * void because the standard stipulates that assert(e)
 * returns no value. 
 */
#undef assert
#ifdef NDEBUG
# define assert(e) ((void)0)
#else
# include "except.h"
extern void assert(int e);
#define assert(e) ((void)((e)||(RAISE(Assert_Failed), 0)))
#endif
