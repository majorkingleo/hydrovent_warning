/*
 * HydrothermalVentingFileParser.h
 *
 *  Created on: 26.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef SRC_HYDROTHERMALVENTINGFILEPARSER_H_
#define SRC_HYDROTHERMALVENTINGFILEPARSER_H_

#include "FileBaseParser.h"
#include "HydrothermalVentingLine.h"
#include <regex>
#include <variant>
#include <sstream>
#include <algorithm>

/*
 * Regex based file parser
 *
 * On each matching line it allocates an OBJECT class
 * The given OBJECT class has to implement following constructor:
 *    OBJECT( const std::vector<std::string> & matching_groups )
 *
 * The regex has to define matching groups eg: ([0-9])([A-Z])
 * every matching group value will be passed to the cunstructor via the
 * matching_groups vector.
 */
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

	/*
	 * Parses the next line and returns a std::variant of
	 * - OBJECT     (on success)
	 * - ParseError (on failure)
	 * - EndOfFile  (if eof is reached)
	 */
	std::variant<OBJECT,ParseError,EndOfFile> parseNextLine()
	{
		std::string line;
		std::getline( file, line );
		++current_line_number;

		// remove the \r from DOS line endings
		// only required for Linux to create better error messages
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

		/* This part could be improved, by delegating the object creation
		 * to a user defined lambda function
		 */

		std::vector<std::string> groups;
		std::transform( ++matches.begin(),
						matches.end(),
						std::back_inserter(groups),
						[]( auto & match ) { return match.str(); });

		return OBJECT( groups );
	}

	auto getCurrentLineNumber() const {
		return current_line_number;
	}
};

/*
 * expected format:        318,513 -> 404,513
 * regex match groups: (318),(513) -> (404),(513)
 *
 */
class HydrothermalVentingFileParser : public RegexBasedFileParser<HydrothermalVentingLine>
{
public:
	HydrothermalVentingFileParser( const std::string & file_name )
	: RegexBasedFileParser<HydrothermalVentingLine>( file_name,
			// expected format: 318,513 -> 404,513
			 R"regex(([0-9]+)\s*,\s*([0-9]+)\s*->\s*([0-9]+)\s*,\s*([0-9]+)\s*)regex" )
	{}

};


#endif /* SRC_HYDROTHERMALVENTINGFILEPARSER_H_ */
