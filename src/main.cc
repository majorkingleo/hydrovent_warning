/*
 * main.cc
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */
#include "HydrothermalVentingFileParser.h"
#include <iostream>
#include <iomanip>
#include <CrossMap.h>
#include "GetInputFromUser.h"
#include "ProgressInfo.h"

int main( int argc, char *const *argv )
{
	try {
		GetInputFileFromUser ask_for_input_file( "Please specify an input file", argc > 1 ? argv[1] : "" );

		std::string input_file = ask_for_input_file.ask();

		HydrothermalVentingFileParser parser( input_file );

		parser.open();

		ProgressInfo pi( input_file );

		CrossMap map;

		while( !parser.eof() ) {
			auto res = parser.parseNextLine();

			pi.setPercentageProgress( parser.getPercetageProgress() );

			if( std::holds_alternative<HydrothermalVentingLine>( res ) ) {
				HydrothermalVentingLine line = std::move( std::get<HydrothermalVentingLine>(res) );

				if( !line.isValid() ) {
					std::cout << "\n"
							  << "Warning: "
							  << std::setfill('0') << std::setw(5) <<  parser.getCurrentLineNumber()
							  << " skipping invalid line: '"
							  << line
							  << "'"
							  << std::endl;

					// redraw complete progress bar
					pi.setTainted(true);
					continue;
				}

				map.addLine(line);

			} else if( std::holds_alternative<HydrothermalVentingFileParser::EndOfFile>( res ) ) {
				break;

			} else {
				auto error = std::get<HydrothermalVentingFileParser::ParseError>(res);

				std::cout << "\n"
						  << "Error: "
						  << std::setfill('0') << std::setw(5) << error.line_number
						  << " line: '" << error.line << "' "
						  << " error: " << error.error
						  << std::endl;

				// redraw complete progress bar
				pi.setTainted(true);
			}

			pi.paint();
		}

		pi.paint();
		std::cout << "\n\n";

		if( map.getWidth() > 200 ||
			map.getHeight() > 200 ) {

			std::string question =
					"Display map (Size: " + std::to_string( map.getWidth() )
					+ "x"
					+ std::to_string( map.getHeight() );

			GetYesNoFromUser display_map( question );

			if( !display_map.ask().empty() ) {
				std::cout << map << std::endl;
			}
		} else {
			std::cout << map << std::endl;
		}

		auto dangerous_points = map.getDangerousPoints();

		std::cout << "Number of dangerous Points: " << dangerous_points.size() << "\n";
		std::cout << "\n"
				  << dangerous_points;

		GetYesNoFromUser write_output( "Do you wan't to save dangerous points to a file?" );

		if( argc > 2 || !write_output.ask().empty() ) {
			GetOutputFileFromUser output_file_name( "Please enter a file name to save dangerous points", argc > 2 ? argv[2] : "" );

			std::string file_name = output_file_name.ask();

			std::ofstream out( file_name.c_str(), std::ios_base::trunc );
			out << "Number of dangerous Points: " << dangerous_points.size() << "\n";
			out << "\n";
			out << dangerous_points;

			std::cout << "\nDangerous points written to: " << file_name << std::endl;
		}


	} catch( const std::exception & error ) {
		std::cerr << "Error: " << error.what() << std::endl;
	}

	return 0;
}



