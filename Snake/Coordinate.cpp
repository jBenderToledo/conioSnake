#include "pch.h"
#include "Coordinate.h"

Coordinate::Coordinate(
	long x0,
	long y0
) {
	x |= x0;
	y |= y0;
}