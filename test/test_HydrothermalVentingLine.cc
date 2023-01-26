/*
 * test_HydrothermalVentingLine.cc
 *
 *  Created on: 26.01.2023
 *      Author: martin
 */

#ifndef TEST_TEST_HYDROTHERMALVENTINGLINE_CC_
#define TEST_TEST_HYDROTHERMALVENTINGLINE_CC_

#include <HydrothermalVentingFileParser.h>
#include "TestUtils.h"
#include "ColoredOutput.h"
#include "ColBuilder.h"
#include <iostream>

class TestCaseSimple : public TestCaseBase
{
	const std::string x1;
	const std::string y1;
	const std::string x2;
	const std::string y2;

public:
	TestCaseSimple( const std::string & x1,
					const std::string & y1,
					const std::string & x2,
					const std::string & y2,
					const std::string & name,
					bool throws_exception = false )
    : TestCaseBase( format( x1, y2, x2, y2 ) + ": " + name, false ),
      x1(x1),
      y1(y1),
      x2(x2),
      y2(y2)
    {}

    virtual bool run() override
    {
    	std::vector<std::string> vs = { x1, y1, x2, y2 };

    	HydrothermalVentingLine line( vs );

    	return line.isValid();
    }

    static std::string format( int x1, int y1, int x2, int y2 ) {
    	std::stringstream ss;
    	ss << x1 << "," << y1 << " -> " << x2 << "," << y2;

    	return ss.str();
    }

    static std::string format( const std::string & x1,
    						   const std::string & y1,
    						   const std::string & x2,
    						   const std::string & y2 ) {
    	std::stringstream ss;
    	ss << x1 << "," << y1 << " -> " << x2 << "," << y2;

    	return ss.str();
    }
};


int main()
{
	try {

		std::vector<std::shared_ptr<TestCaseBase>> test_cases;
		test_cases.push_back( std::make_shared<TestCaseSimple>("1", "1", "2", "2", "simple 45°", false ) );


		ColBuilder col;
		ColoredOutput co;


		const int COL_IDX       = col.addCol( "Idx" );
		const int COL_NAME      = col.addCol( "Test" );
		const int COL_RESULT    = col.addCol( "Result" );
		const int COL_EXPTECTED = col.addCol( "Expected" );
		const int COL_TEST_RES  = col.addCol( "Test Result" );

		unsigned idx = 0;

		for( auto & test : test_cases ) {

			idx++;

			col.addColData( COL_IDX, std::to_string(idx) );
			col.addColData( COL_NAME, test->getName() );

			std::string result;
			std::string expected_result = "true";
			std::string test_result;

			try {

				if( test->throwsException() ) {
					expected_result = "exception";
				}

				if( test->run() ) {
					result = "true";
				} else {
					result = "false";
				}
			} catch( const std::exception & error ) {
				result = "exception";
			} catch( ... ) {
				result = "exception";
			}

			if( result != expected_result ) {
				test_result = co.color_output( ColoredOutput::RED, "failed" );
			} else {
				test_result = co.color_output( ColoredOutput::GREEN, "succeeded" );
			}

			col.addColData( COL_RESULT, result );
			col.addColData( COL_EXPTECTED, expected_result );
			col.addColData( COL_TEST_RES, test_result );
		}


		std::cout << col.toString() << std::endl;

	} catch( std::exception & error ) {
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}


#endif /* TEST_TEST_HYDROTHERMALVENTINGLINE_CC_ */
