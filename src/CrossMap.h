/*
 * CrossingMap.h
 *
 *  Created on: 27.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef SRC_CROSSMAP_H_
#define SRC_CROSSMAP_H_

#include "HydrothermalVentingLine.h"

#include <vector>
#include <ostream>

/**
 * CrossMap class
 *
 * The speed of this implementation could be better,
 * but would also consume more memory.
 *
 * Other improvements would be possible if the
 * maximum world coordinates are known.
 *
 */
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

	/* Adds a new HydrothermalVentingLine to the map.
	 * The map will be automatically extended if required.
	 */
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

/* Generates the map in ASCII style
 * 1.1....11.
 * .111...2..
 * ..2.1.111.
 * ...1.2.2..
 * .112313211
 * ...1.2....
 * ..1...1...
 * .1.....1..
 * 1.......1.
 * 222111....
 */
std::ostream & operator<<( std::ostream & out, const CrossMap & cross_map );

/* converts one dangerous point to hydrothermal vent crossroad format
 * eg: (5, 5) -> 2
 */
std::ostream & operator<<( std::ostream & out, const CrossMap::DangerousPoint & point );

/*
 * converts a vector of dangerous points to hydrothermal vent crossroad format without the header
 *
 * eg:
 * (0, 9) -> 2
 * (1, 9) -> 2
 * (2, 2) -> 2
 * (2, 9) -> 2
 * (3, 4) -> 2
 * (4, 4) -> 3
 *
 */
std::ostream & operator<<( std::ostream & out, const std::vector<CrossMap::DangerousPoint> & points );
#endif /* SRC_CROSSMAP_H_ */
