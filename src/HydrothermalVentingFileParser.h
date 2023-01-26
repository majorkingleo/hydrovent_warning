/*
 * HydrothermalVentingFileParser.h
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */

#ifndef SRC_HYDROTHERMALVENTINGFILEPARSER_H_
#define SRC_HYDROTHERMALVENTINGFILEPARSER_H_

#include "FileBaseParser.h"
#include <regex>
#include <variant>
#include <sstream>
#include <algorithm>

template <class OBJECT> class RegexBasedFileParser : public FileBaseParser
{
public:
	class ParseError
	{
	public:
		unsigned line_number;
		std::string line;
		std::string error;
	};

	struct EndOfFile {};

protected:
	const std::string REGEX_FORMAT;
	const std::regex REGEX;

	unsigned current_line_number;

public:
	RegexBasedFileParser( const std::string & file_name,
						  const std::string & regex_format )
	: FileBaseParser( file_name ),
	  REGEX_FORMAT( regex_format ),
	  REGEX( regex_format.c_str() ),
	  current_line_number(0)
	{}

	std::variant<OBJECT,ParseError,EndOfFile> parseNextLine()
	{
		std::string line;
		std::getline( file, line );
		++current_line_number;

		// remove the \r from DOS line endings
		// only required on linux to create better error messages
		if( !line.empty() && *line.rbegin() == '\r' ) {
			line.resize(line.size()-1);
		}


		if( line.empty() && file.eof() ) {
			return EndOfFile();
		}

		std::smatch matches;
		if( !std::regex_search( line, matches, REGEX ) ) {
			std::stringstream ss;
			ss << "Regex '"
			   << REGEX_FORMAT << "' does not match.";
			return ParseError( { current_line_number, line, ss.str() } );
		}

		std::vector<std::string> groups;
		std::transform( ++matches.begin(),
						matches.end(),
						std::back_inserter(groups),
						[]( auto & match ) { return match.str(); });

		return OBJECT( groups );
	}
};

class HydrothermalVentingLine
{
	class Point
	{
	public:
		unsigned long x;
		unsigned long y;
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

	/**
	 * tests if this a valid line
	 *   - horizantal
	 *   - vertical
	 *   - 45° lines and any multiples of 45° are allowed
	 */
	bool isValid() const;
};

class HydrothermalVentingFileParser : public RegexBasedFileParser<HydrothermalVentingLine>
{
public:
	HydrothermalVentingFileParser( const std::string & file_name )
	: RegexBasedFileParser<HydrothermalVentingLine>( file_name,
			// expected format: 318,513 -> 404,513
			 R"regex(([0-9]+),([0-9]+)\s*->\s*([0-9]+),([0-9]+)\s*)regex" )
	{}

};


#endif /* SRC_HYDROTHERMALVENTINGFILEPARSER_H_ */
