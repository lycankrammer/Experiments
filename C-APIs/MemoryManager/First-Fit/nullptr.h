/********************************************
 *                                          *
 *        C Header file: nullptr.h          *
 *                                          *
 ********************************************/
#ifndef NULLPTR_H
#define NULLPTR_H 1

#ifndef nullptr
typedef void* __nullptr_t;
#define nullptr ((__nullptr_t)+0)
#endif

#endif
