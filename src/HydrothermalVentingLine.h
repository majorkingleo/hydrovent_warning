/*
 * HydrothermalVentingLine.h
 *
 *  Created on: 27.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef SRC_HYDROTHERMALVENTINGLINE_H_
#define SRC_HYDROTHERMALVENTINGLINE_H_

#include <ostream>
#include <string>
#include <vector>

class HydrothermalVentingLine
{
public:
	class Point
	{
	public:
		unsigned long x;
		unsigned long y;

		bool operator<( const Point & other ) const {
			if( x < other.x ) {
				return true;
			}

			if( y < other.y ) {
				return true;
			}

			return false;
		}

		bool operator>( const Point & other ) const {
			if( x > other.x ) {
				return true;
			}

			if( y > other.y ) {
				return true;
			}

			return false;
		}

		bool operator==( const Point & other ) const {

			if( x == other.x &&
				y == other.y ) {
				return true;
			}

			return false;
		}
	};

	Point start;
	Point end;

public:
	HydrothermalVentingLine( std::vector<std::string> & matches )
	: start( { std::stoul( matches[0] ),
			   std::stoul( matches[1] ) } ),
	  end (  { std::stoul( matches[2] ),
			   std::stoul( matches[3] ) } )
	{}

	HydrothermalVentingLine( unsigned long x1,
							 unsigned long y1,
							 unsigned long x2,
							 unsigned long y2 )
	: start( { x1, y1 } ),
	  end (  { x2, y2 } )
	{}

	/**
	 * tests if this is a valid line
	 *   - horizantal
	 *   - vertical
	 *   - 45° lines and any multiples of 45° are allowed
	 */
	bool isValid() const;

	const Point & getStart() const {
		return start;
	}

	const Point & getEnd() const {
		return end;
	}
};

/* converts one HydrothermalVentingLine to: 1,1 -> 2,2 */
std::ostream & operator<<( std::ostream & out, const HydrothermalVentingLine & line );

#endif /* SRC_HYDROTHERMALVENTINGLINE_H_ */
