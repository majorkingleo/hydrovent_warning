/*
 * CrossingMap.cc
 *
 *  Created on: 27.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */
#include "CrossMap.h"

#include <iostream>

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
			++cross_map.at(x).at(y);
		}
	}
	// horizontal
	else if( start.y == end.y ) {
		auto y = start.y;
		for( auto x = start.x; x <= end.x; x++ ) {
			++cross_map.at(x).at(y);
		}
	}
	// diagonal
	else if( start.x < end.x && start.y < end.y ) {
		for( auto x = start.x, y = start.y; x <= end.x && y <= end.y; x++, y++ ) {
			++cross_map.at(x).at(y);
		}
	}
	else {
		if( start.x < end.x && start.y > end.y ) {
			std::swap( start, end );
		}

		for( int x = start.x, y = start.y; x >= end.x && y <= end.y; x--, y++ ) {
			// std::cout << x << "," << y << std::endl;
			++cross_map.at(x).at(y);
		}
	}
}

void CrossMap::expandMap( unsigned long x, unsigned long y )
{
	if( cross_map.size() <= x ) {
		cross_map.resize(x+1);

		auto height = getHeight();

		// enlarge all y rows
		for( auto & y_row : cross_map ) {
			y_row.resize( std::max(y+1,height) );
		}
	}

	if( cross_map.empty() || cross_map[0].size() <= y ) {
		// enlarge all y rows
		for( auto & y_row : cross_map ) {
			y_row.resize(y+1);
		}
	}
}

std::vector<CrossMap::DangerousPoint> CrossMap::getDangerousPoints() const
{
	auto width = getWidth();
	auto height = getHeight();

	std::vector<DangerousPoint> dangerous_points;

	/* if we would have only one vector here (with known maximum coordinates)
	 * we could use filters here
	 *
	 * or running parallel with openmp
	 */

	for( MAP_TYPE::size_type x = 0; x < width; x++ ) {
		for( MAP_TYPE::size_type y = 0; y < height; y++ ) {

			auto number_of_dangerous_lines = cross_map.at(x).at(y);
			if( number_of_dangerous_lines >= 2 ) {
				dangerous_points.push_back( DangerousPoint( x, y, number_of_dangerous_lines ) );
			}
		}
	}

	return dangerous_points;
}

std::ostream & operator<<( std::ostream & out, const CrossMap & cross_map )
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

std::ostream & operator<<( std::ostream & out, const CrossMap::DangerousPoint & point )
{
	return out << "(" << point.x << ", " << point.y << ") -> " << point.number_of_crossing_venting_lines;
}

std::ostream & operator<<( std::ostream & out, const std::vector<CrossMap::DangerousPoint> & points )
{
	for( auto & point : points ) {
		out << point << '\n';
	}

	return out;
}
