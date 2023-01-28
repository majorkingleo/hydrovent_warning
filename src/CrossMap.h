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
public:
	class DangerousPoint : public HydrothermalVentingLine::Point
	{
	public:
		unsigned long number_of_crossing_venting_lines;

	public:
		DangerousPoint()
		: HydrothermalVentingLine::Point( {0,0} ),
		  number_of_crossing_venting_lines(0)
		{}

		DangerousPoint( unsigned long x,
						unsigned long y,
						unsigned long number_of_crossing_venting_lines )
		: HydrothermalVentingLine::Point( {x, y } ),
		  number_of_crossing_venting_lines( number_of_crossing_venting_lines )
		{}
	};

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

	const auto & operator[]( MAP_TYPE::size_type idx ) const {
		return cross_map[idx];
	}

	auto & at( MAP_TYPE::size_type idx ) {
		return cross_map.at(idx);
	}

	std::vector<DangerousPoint> getDangerousPoints() const;

private:
	void expandMap( const HydrothermalVentingLine::Point & point ) {
		expandMap( point.x, point.y );
	}
	void expandMap( unsigned long x, unsigned long y );
};

std::ostream & operator<<( std::ostream & out, const CrossMap & cross_map );
std::ostream & operator<<( std::ostream & out, const CrossMap::DangerousPoint & point );
std::ostream & operator<<( std::ostream & out, const std::vector<CrossMap::DangerousPoint> & points );
#endif /* SRC_CROSSMAP_H_ */
