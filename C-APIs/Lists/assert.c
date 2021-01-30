/**********************************************
 *                                            *
 *           C File: assert.c                 *
 *                                            *
 **********************************************/
#include "assert.h"

const Except_T Assert_Failed = { "Assertion failed" };

/** The parentheses around the name assert int the function
 * definition supresses expansion of the macro assert and thus
 * define the function, as required by the interface.
 */
void (assert)(int e) {
	assert(e);
}
