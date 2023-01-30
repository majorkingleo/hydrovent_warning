/*
 * FileBaseParser.h
 *
 *  Created on: 26.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
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

	/* opens the file */
	bool open();

	/* returns a number between 0 an 100
	 * assumes that the current file position reported by tellg()
	 * is your current progress in file parsing.
	 */
	unsigned getPercetageProgress() {
		calculateProgress();
		return progress;
	}

	/* return true if end of file is reached */
	bool eof() const {
		return file.eof();
	}

protected:
	void calculateProgress();

};



#endif /* SRC_FILEBASEPARSER_H_ */
