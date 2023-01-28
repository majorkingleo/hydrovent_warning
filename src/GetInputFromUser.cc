/*
 * GetInputFromUser.cc
 *
 *  Created on: 28.01.2023
 *      Author: martin
 */
#include "GetInputFromUser.h"
#include <iostream>
#include <filesystem>

std::string GetInputFromUser::ask()
{
	do {
		std::cout << question << " : " << std::flush;

		std::string answer;
		std::getline( std::cin, answer );

		if( isValid( answer ) ) {
			return answer;
		}
	} while( true );

	return std::string();
}

std::string GetInputFileFromUser::ask()
{
	if( isValid( argv_value )  ) {
		return argv_value;
	}

	return GetInputFromUser::ask();
}

bool GetInputFileFromUser::isValid( const std::string & answer )
{
	namespace fs = std::filesystem;

	if( fs::is_regular_file(fs::status(answer)) ) {
		return true;
	}

	std::cout << "This is not a valid file. Please try it again or press CTRL+C to abort.\n";

	return false;
}

bool GetYesNoFromUser::isValid( const std::string & answer )
{
	std::string text = answer;
	text.resize(1);

	if( text == "Y" ||
		text == "y" ) {
		return true;
	}

	return false;
}
