/*
 * FileBaseParser.cc
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */
#include "FileBaseParser.h"
#include <filesystem>
#include <iostream>

bool FileBaseParser::open()
{
	file_size = std::filesystem::file_size( file_name );

	file.open( file_name );

	if( !file ) {
		return false;
	}

	calculateProgress();

	return true;
}

void FileBaseParser::calculateProgress()
{
	auto pos = file.tellg();

	if( file.eof() ) {
		progress = 100;
	} else {
		progress = pos * 100.0 / file_size;
	}
}

