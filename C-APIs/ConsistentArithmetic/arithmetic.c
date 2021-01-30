//==========================================================
// This library provides the utilities max and min, and  con_
// sistent use of arithmetic  operations  division,  modulus,
// division ceiling and floor.
// See arithmetic.h for more info.
//==========================================================
#include "arithmetic.h"

//======================================
// Arith_max
//======================================
int Arith_max(int x, int y)
{
	return x > y ? x : y;
}

//======================================
// Arith_min
//======================================
int Arith_min(int x, int y)
{
	return x < y ? x : y;
}

//======================================
// Arith_div
//====================================== 
int Arith_div(int x, int y)
{
	int quotienti = x/y;
	double quotientf = (double) x/y;
	// If the  signs of  x and y are different, the division
	// truncates toward zero, and y doesn't divides x evenly.
	if ((x < 0) != (y < 0) && (double) quotienti > quotientf && x%y != 0) {
		return quotienti - 1;
	}
	else {
		return quotienti;
	}
}

//======================================
// Arith_mod
//======================================
int Arith_mod(int x, int y)
{
	return x - y*Arith_div(x, y);
}

//======================================
// Arith_floor
//======================================
int Arith_floor(int x, int y)
{
	return Arith_div(x, y);
}

//======================================
// Arith_ceiling
//======================================
int Arith_ceiling(int x, int y)
{
	return Arith_div(x, y) + (x%y != 0);
}
