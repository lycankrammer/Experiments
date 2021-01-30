//==========================================================
// This library provides the utilities max and min, and  con_
// sistent use of arithmetic  operations  division,  modulus,
// division ceiling and floor.
//==========================================================
#ifndef ARITHMETIC_H
#define ARITHMETIC_H 1

// Arith_div returns the quotient obtained by dividing  x by y,
// and Arith_mod returns the corresponding remainder.  When  x
// and y are both positive or both  negative,  Arith_div(x, y)
// is equal to x/y and Arith_mod(x, y) is equal to  x%y.  When
// the operands have different signs, the values  returned  by
// C's built-in operators depend on the implementation. When y
// is zero, Arith_div  and  Arith_mod behave  the same as  the
// built-in counterparts.
// The C  Standard  insists only that if x/y is  representable,
// then (x/y)y + x%y must be equal to x.  These  semantics per_
// mit integer division to truncate toward zero or towar minus
// infinity when exactly one of the operands is negative.  For
// example, if -13/5 is -2, then the standard says  that -13%5
// must be equal to -13 - (-13/5)5 = -13 - (-2)5 = -3. But  if
// -13/5 is -3, then the value -13%5 must be -13 - (-3)5 = 2.
//
// Arith_div and Arith_mod are well-defined. They always  trun_
// cate toward the left on the  number line; toward  zero when
// their operands have the same sign, and toward minus  infini_
// ty when their signs are different.
// The definitions for Arith_div and Arith_mod are  couched in
// more  precise  mathematical  terms. Arith_div(x, y) is  the
// maximum integer that does not exceed the real number z such
// that  z*y = x. Arith_mod(x, y)  is defined  to be equal  to
// x - y*Arith_div(x, y).
//
// The functions Arith_ceiling and Arith_floor follow  similar
// conventions. Arith_ceiling(x, y) returns  the least integer
// not less than the real quotient of x/y,  and  Arith_floor(x,
// y) returns the greatest integer not exceeding the real  quo_
// tient of x/y. That is, Arith_ceiling returns the integer to
// the right  of x/y on the number line,  and  Arith_floor  re_
// turns the integer to the left of x/y for all operands.

extern int Arith_max(int x, int y);
extern int Arith_min(int x, int y);
extern int Arith_div(int x, int y);
extern int Arith_mod(int x, int y);
extern int Arith_ceiling(int x, int y);
extern int Arith_floor(int x, int y);

#endif
