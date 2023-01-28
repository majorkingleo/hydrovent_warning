/*
 * GetInputFromUser.cc
 *
 *  Created on: 28.01.2023
 *      Author: martin
 */
#include "GetInputFromUser.h"
#include <iostream>
#include <filesystem>
#include <fstream>

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
	if( !argv_value.empty() && isValid( argv_value )  ) {
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

std::string GetYesNoFromUser::ask()
{
	std::string text = GetInputFromUser::ask();

	if( text.find('Y') == 0 ||
		text.find('y') == 0 ) {
		return text;
	}

	return std::string();
}

bool GetYesNoFromUser::isValid( const std::string & answer )
{
	std::string text = answer;
	text.resize(1);

	if( text == "Y" ||
		text == "y" ||
		text == "N" ||
		text == "n" ) {
		return true;
	}

	return false;
}


std::string GetOutputFileFromUser::ask()
{
	if( !argv_value.empty() && isValid( argv_value )  ) {
		return argv_value;
	}

	return GetInputFromUser::ask();
}

bool GetOutputFileFromUser::isValid( const std::string & answer )
{
	std::fstream out( answer.c_str() );

	if( !out ) {
		std::cout << "Cannot write to file '" << answer << "' please try it again!\n";
		return false;
	}

	return true;
}
