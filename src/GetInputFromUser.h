/*
 * GetInputFromUser.h
 *
 *  Created on: 28.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef SRC_GETINPUTFROMUSER_H_
#define SRC_GETINPUTFROMUSER_H_

#include <string>

/*
 * Base class for asking a question and getting an answer
 * from user on command line, by simple using std::cin
 *
 * This could be improved by using gnu readline lib
 */
class GetInputFromUser
{
	std::string question;
public:

	GetInputFromUser( const std::string & question )
	: question( question )
	{}

	/* start interaction and wait for input */
	virtual std::string ask();

protected:
	virtual bool isValid( const std::string & answer ) {
		return true;
	}
};

/*
 * Asks the user for a input file. The file has to exists.
 */
class GetInputFileFromUser : public GetInputFromUser
{
	const std::string argv_value;

public:
	GetInputFileFromUser( const std::string & question, const std::string & argv_value = "" )
	: GetInputFromUser( question ),
	  argv_value( argv_value )
	{}

	std::string ask() override;

protected:
	bool isValid( const std::string & answer ) override;
};

/*
 * Asks the user a yes/no question
 */
class GetYesNoFromUser : public GetInputFromUser
{
	std::string question;
public:

	GetYesNoFromUser( const std::string & question_ )
	: GetInputFromUser( question_ + "(Y/N)" )
	{}

	// returns an empty string in case of a "no"
	std::string ask();

protected:
	bool isValid( const std::string & answer ) override;
};


/*
 * Asks the user for a output file.
 * Tests if the file can be opened for writing.
 */
class GetOutputFileFromUser : public GetInputFromUser
{
	const std::string argv_value;

public:
	GetOutputFileFromUser( const std::string & question, const std::string & argv_value = "" )
	: GetInputFromUser( question ),
	  argv_value( argv_value )
	{}

	std::string ask() override;

protected:
	bool isValid( const std::string & answer ) override;
};

#endif /* SRC_GETINPUTFROMUSER_H_ */
