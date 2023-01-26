/*
 * HydrothermalVentingFileParser.cc
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */
#include "HydrothermalVentingFileParser.h"

bool HydrothermalVentingLine::isValid() const
{
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

	if( x_diff == y_diff ) {
		return true;
	}

	return false;
}
