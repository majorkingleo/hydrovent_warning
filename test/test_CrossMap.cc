/*
 * test_CrossMap.cc
 *
 *  Created on: 27.01.2023
 *      Author: martin
 */

#ifndef TEST_TEST_CROSSMAP_CC_
#define TEST_TEST_CROSSMAP_CC_

#include <CrossMap.h>
#include "TestUtils.h"
#include "ColoredOutput.h"
#include <iostream>
#include <memory>
#include <sstream>

using Point = HydrothermalVentingLine::Point;

class TestCaseSimple : public TestCaseBase<std::string>
{
	std::vector<HydrothermalVentingLine> lines;

public:
	TestCaseSimple( const std::vector<HydrothermalVentingLine> & lines,
					const std::string & name,
					const std::string & expected_result,
					bool throws_exception = false )
    : TestCaseBase( name, expected_result, false ),
      lines(lines)
    {}

    virtual std::string run() override
    {
    	CrossMap cross_map;

    	for( auto & line : lines ) {
    		cross_map.addLine( line );
    	}

    	std::stringstream ss;
    	ss << cross_map;

    	return ss.str();
    }



};

std::shared_ptr<TestCaseSimple> createTestCase1()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 0,0, 0,5 )
	};

	return std::make_shared<TestCaseSimple>( lines,
			"vertical 5",
R"(1
1
1
1
1
1
)" );
}

int main()
{
	try {

		std::vector<std::shared_ptr<TestCaseBase<std::string>>> test_cases;
		test_cases.push_back( createTestCase1() );

		ColoredOutput co;
		unsigned idx = 0;

		for( auto & test : test_cases ) {

			idx++;

			std::cout << " ### " << idx << " ============ Test: " << test->getName() << " ==============\n";

			std::string result;
			std::string expected_result = test->getExpectedResult();

			std::string test_result;

			try {

				if( test->throwsException() ) {
					expected_result = "exception";
				}

				result = test->run();

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

			std::cout << "Result:\n----------------\n" << result
					  << "\n^^^^^^^^^^^^^^^^^^^\n";
			std::cout << "Expedted Result:\n----------------\n" << expected_result
					  << "\n^^^^^^^^^^^^^^^^^^^\n";
			std::cout << "Test case: " <<  test_result
					  << "\n"
					  << "\n\n";
		}



	} catch( std::exception & error ) {
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}


#endif /* TEST_TEST_HYDROTHERMALVENTINGLINE_CC_ */
