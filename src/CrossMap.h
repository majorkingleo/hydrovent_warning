/*
 * CrossingMap.h
 *
 *  Created on: 27.01.2023
 *      Author: martin
 */

#ifndef SRC_CROSSMAP_H_
#define SRC_CROSSMAP_H_

#include "HydrothermalVentingLine.h"

#include <vector>
#include <ostream>

class CrossMap
{
private:
	// map x,y,n
	//     n: number of lines, crossing this point
	//
	// orientation: (like display screens)
	//     left to right: x
	//     top to button: y
	using MAP_TYPE = std::vector< std::vector< unsigned long >>;

	MAP_TYPE cross_map;

public:
	CrossMap();

	void addLine( const HydrothermalVentingLine & line );

	unsigned long getWidth() const {
		return cross_map.size();
	}

	unsigned long getHeight() const {
		if( cross_map.empty() ) {
			return 0;
		}

		return cross_map.at(0).size();
	}

	auto & operator[]( MAP_TYPE::size_type idx ) {
		return cross_map[idx];
	}

	auto & at( MAP_TYPE::size_type idx ) {
		return cross_map.at(idx);
	}

private:
	void expandMap( const HydrothermalVentingLine::Point & point ) {
		expandMap( point.x, point.y );
	}
	void expandMap( unsigned long x, unsigned long y );
};

std::ostream & operator<<( std::ostream & out, CrossMap & cross_map );

#endif /* SRC_CROSSMAP_H_ */
