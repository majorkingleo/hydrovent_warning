/*
 * TestUtils.h
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */

#ifndef TEST_TESTUTILS_H_
#define TEST_TESTUTILS_H_

#include <string>

class TestCaseBase
{
protected:
    std::string name;
    bool throws_exception;

public:
    TestCaseBase( const std::string & name_, bool throws_exception_ = false )
    : name( name_ ),
      throws_exception( throws_exception_ )
    {}

    virtual ~TestCaseBase() {}

    virtual bool run() = 0;

    const std::string & getName() const {
        return name;
    }

    bool throwsException() const {
        return throws_exception;
    }
};



#endif /* TEST_TESTUTILS_H_ */
