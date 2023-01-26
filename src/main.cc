/*
 * main.cc
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */
#include "HydrothermalVentingFileParser.h"
#include <iostream>
#include <iomanip>

int main()
{
	try {
		HydrothermalVentingFileParser parser( "test.txt" );

		parser.open();

		while( !parser.eof() ) {
			auto res = parser.parseNextLine();

			if( std::holds_alternative<HydrothermalVentingLine>( res ) ) {
				HydrothermalVentingLine line = std::move( std::get<HydrothermalVentingLine>(res) );

			} else if( std::holds_alternative<HydrothermalVentingFileParser::EndOfFile>( res ) ) {
				break;

			} else {
				auto error = std::get<HydrothermalVentingFileParser::ParseError>(res);

				std::cout << std::setfill('0') << std::setw(5) << error.line_number
						  << " line: '" << error.line << "' "
						  << " error: " << error.error
						  << std::endl;
			}

		}

	} catch( const std::exception & error ) {
		std::cerr << "Error: " << error.what() << std::endl;
	}
}



