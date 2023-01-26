/*
 * FileBaseParser.h
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */

#ifndef SRC_FILEBASEPARSER_H_
#define SRC_FILEBASEPARSER_H_

#include <fstream>
#include <string>

class FileBaseParser
{
protected:
	std::string file_name;
	std::fstream file;
	std::uintmax_t file_size;
	unsigned progress;


public:
	FileBaseParser( const std::string & file_name_ )
	: file_name( file_name_ ),
	  file()
	{}

	bool open();

	/* returns a number between 0 an 100 */
	unsigned getPercetageProgress() const {
		return progress;
	}

	bool eof() const {
		return file.eof();
	}

protected:
	void calculateProgress();

};



#endif /* SRC_FILEBASEPARSER_H_ */
