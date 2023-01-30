/*
 * HydrothermalVentingLine.cc
 *
 *  Created on: 27.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#include "HydrothermalVentingLine.h"

bool HydrothermalVentingLine::isValid() const
{
	// it is a point
	if( start == end ) {
		return false;
	}

	// vertical
	if( start.x == end.x ) {
		return true;
	}

	// horizontal
	if( start.y == end.y ) {
		return true;
	}

	int x1 = std::min( start.x, end.x );
	int x2 = std::max( start.x, end.x );

	int y1 = std::min( start.y, end.y );
	int y2 = std::max( start.y, end.y );

	int x_diff = x2 - x1;
	int y_diff = y2 - y1;

	// only when x_diff equals y_diff we have 45° use case
	if( x_diff == y_diff ) {
		return true;
	}

	return false;
}

std::ostream & operator<<( std::ostream & out, const HydrothermalVentingLine & line )
{
	out << line.getStart().x << ',' << line.getStart().y
		<< " -> "
		<< line.getEnd().x << ',' << line.getEnd().y;

	return out;
}
