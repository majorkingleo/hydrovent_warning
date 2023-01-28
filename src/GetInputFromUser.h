/*
 * GetInputFromUser.h
 *
 *  Created on: 28.01.2023
 *      Author: martin
 */

#ifndef SRC_GETINPUTFROMUSER_H_
#define SRC_GETINPUTFROMUSER_H_

#include <string>

class GetInputFromUser
{
	std::string question;
public:

	GetInputFromUser( const std::string & question )
	: question( question )
	{}

	virtual std::string ask();

protected:
	virtual bool isValid( const std::string & answer ) {
		return true;
	}
};

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

class GetYesNoFromUser : public GetInputFromUser
{
	std::string question;
public:

	GetYesNoFromUser( const std::string & question_ )
	: GetInputFromUser( question_ + "(Y/N)" )
	{}

	std::string ask();

protected:
	bool isValid( const std::string & answer ) override;
};


#endif /* SRC_GETINPUTFROMUSER_H_ */
