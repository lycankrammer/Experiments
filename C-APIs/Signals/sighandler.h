
/*******************************************
 *                                         *
 *      C Header file: sighandler.h        *
 *                                         *
 *******************************************/
#ifndef SIGHANDLER_H
#define SIGHANDLER_H 1

#include <signal.h>
#include <stdio.h>
#ifndef __STDC_NO_ATOMIC__
#include <stdatomic.h>
#endif

/** A pair of strings to hold signal info.
 */
typedef struct sh_pair sh_pair;
struct sh_pair {
	const char *name;
	const char *desc;
};

/** The size of this array can be queried with sh_known.
 * see SH_PRINT to use that information. 
 */
extern const sh_pair sh_pairs[];
extern const size_t sh_known;

#if ATOMIC_LONG_LOCK_FREE > 1
/** Keep track of the number of calls into
 * a signal handler for each possible signal.
 * 
 * Don't use this array directly.
 * 
 * see sh_count to update this information.
 * see SH_PRINT to use that information.
 */
extern _Atomic unsigned long sh_counts[];

/***************************************
 * Use this in your signal handler to  *
 * keep track of the number of calls   *
 * to the signal sig.                  *
 * see sh_counted to use that info.    *
 ***************************************/
inline void sh_count(int sig)
{
	if (sig < sh_known)
		++sh_counts[sig];
}

inline unsigned long sh_counted(int sig)
{
	return (sig < sh_known) ? sh_counts[sig] : 0;
}

#else
inline void sh_count(int sig)
{
	//** empty.
}

inline unsigned long sh_counted(int sig)
{
	return 0;
}

#endif

/** Prototype of signal handlers.
 */
typedef void sh_handler(int);

/** Pretty-prints signal information.
 * 
 * see PRINT_SIG for a convenient user interface.
 */
void sh_print(FILE *io, int sig, const char *filename, size_t line,
              const char *string);

/** Pretty-prints signal information.
 * 
 * This prints signal info STRING for signal SIG to stream IO
 */
#define SH_PRINT(IO, SIG, STRING) sh_print(IO, SIG, __FILE__, __LINE__, STRING)

/** Enables a signal handler and catches the errors.
 */
sh_handler *sh_enable(int sig, sh_handler *hnd);

#endif
