/*
 * CrossingMap.cc
 *
 *  Created on: 27.01.2023
 *      Author: martin
 */
#include "CrossMap.h"

CrossMap::CrossMap()
: cross_map()
{

}

void CrossMap::addLine( const HydrothermalVentingLine & line )
{
	auto start = line.getStart();
	auto end = line.getEnd();

	// resize map if required
	expandMap( start );
	expandMap( end );

	if( start > end ) {
		std::swap( start, end );
	}

	// vertical
	if( start.x == end.x ) {
		auto x = start.x;
		for( auto y = start.y; y <= end.y; y++ ) {
			++cross_map[x][y];
		}
	}
	// horizontal
	else if( start.y == end.y ) {
		auto y = start.y;
		for( auto x = start.x; x <= end.x; x++ ) {
			++cross_map[x][y];
		}
	}
	// diagonal
	else {
		for( auto x = start.x, y = start.y; x <= end.x && y <= end.y; x++, y++ ) {
			++cross_map[x][y];
		}
	}
}

void CrossMap::expandMap( unsigned long x, unsigned long y )
{
	if( cross_map.size() <= x ) {
		cross_map.resize(x+1);

		// enlarge all y rows
		for( auto & y_row : cross_map ) {
			y_row.resize(y+1);
		}
	}

	if( cross_map.empty() || cross_map[0].size() <= y ) {
		// enlarge all y rows
		for( auto & y_row : cross_map ) {
			y_row.resize(y+1);
		}
	}
}

std::ostream & operator<<( std::ostream & out, CrossMap & cross_map )
{
	auto width = cross_map.getWidth();
	auto height = cross_map.getHeight();

	for( auto y = 0; y < height; y++ ) {
		for( auto x = 0; x < width; x++ ) {
			if( cross_map[x][y] == 0 ) {
				out << '.';
			} else {
				out << cross_map[x][y];
			}
		}
		out << '\n';
	}

	return out;
}
