/*
 * test_CrossMap.cc
 *
 *  Created on: 27.01.2023
 *      Author: Martin Oberzalek <oberzalek@gmx.at>
 */

#ifndef TEST_TEST_CROSSMAP_CC_
#define TEST_TEST_CROSSMAP_CC_

#include <CrossMap.h>
#include "TestUtils.h"
#include "ColoredOutput.h"
#include "ColBuilder.h"
#include <iostream>
#include <memory>
#include <sstream>

using Point = HydrothermalVentingLine::Point;

class TestCaseMap : public TestCaseBase<std::string>
{
	std::vector<HydrothermalVentingLine> lines;

public:
	TestCaseMap( const std::vector<HydrothermalVentingLine> & lines,
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

class TestCaseDangerousPoints : public TestCaseBase<std::string>
{
	std::vector<HydrothermalVentingLine> lines;

public:
	TestCaseDangerousPoints( const std::vector<HydrothermalVentingLine> & lines,
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
    	ss << cross_map.getDangerousPoints();

    	return ss.str();
    }
};


std::shared_ptr<TestCaseMap> createTestCase1()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 0,0, 0,5 )
	};

	return std::make_shared<TestCaseMap>( lines,
			"vertical 5,0",
R"(1
1
1
1
1
1
)" );
}

std::shared_ptr<TestCaseMap> createTestCase2()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 0,0, 5,0 )
	};

	return std::make_shared<TestCaseMap>( lines,
			"horizontal 0,5",
			"111111\n");
}

std::shared_ptr<TestCaseMap> createTestCase3()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 5,0, 5,5 )
	};

	return std::make_shared<TestCaseMap>( lines,
			"vertical 0,5",
R"(.....1
.....1
.....1
.....1
.....1
.....1
)" );
}

std::shared_ptr<TestCaseMap> createTestCase4()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 5,0, 5,5 ),
		HydrothermalVentingLine( 0,0, 0,5 )
	};

	return std::make_shared<TestCaseMap>( lines,
			"vertical 0,0 and 0,5",
R"(1....1
1....1
1....1
1....1
1....1
1....1
)" );
}

std::shared_ptr<TestCaseMap> createTestCase5()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 5,0, 5,5 ),
		HydrothermalVentingLine( 5,0, 5,2 ),
		HydrothermalVentingLine( 0,0, 0,5 )
	};

	return std::make_shared<TestCaseMap>( lines,
			"vertical 3 lines",
R"(1....2
1....2
1....2
1....1
1....1
1....1
)" );
}


std::shared_ptr<TestCaseMap> createTestCase6()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 0,0, 5,5 ),
	};

	return std::make_shared<TestCaseMap>( lines,
			"diagonal 0,0",
R"(1.....
.1....
..1...
...1..
....1.
.....1
)" );
}

std::shared_ptr<TestCaseMap> createTestCase7()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 0,5, 5,0 ),
	};

	return std::make_shared<TestCaseMap>( lines,
			"diagonal 0,5",
R"(.....1
....1.
...1..
..1...
.1....
1.....
)" );
}


std::shared_ptr<TestCaseMap> createTestCase8()
{
	std::vector<HydrothermalVentingLine> lines = {
		HydrothermalVentingLine( 5,0, 0,5 ),
	};

	return std::make_shared<TestCaseMap>( lines,
			"diagonal 0,5 reverse",
R"(.....1
....1.
...1..
..1...
.1....
1.....
)" );
}

std::shared_ptr<TestCaseMap> createTestCase9()
{
	// all lines from the example without the last one which is invalid
	std::vector<HydrothermalVentingLine> lines = {
			HydrothermalVentingLine( 0,9, 5,9 ),
			HydrothermalVentingLine( 8,0, 0,8 ),
			HydrothermalVentingLine( 9,4, 3,4 ),
			HydrothermalVentingLine( 2,2, 2,1 ),
			HydrothermalVentingLine( 7,0, 7,4 ),
			HydrothermalVentingLine( 6,4, 2,0 ),
			HydrothermalVentingLine( 0,9, 2,9 ),
			HydrothermalVentingLine( 3,4, 1,4 ),
			HydrothermalVentingLine( 0,0, 8,8 ),
			HydrothermalVentingLine( 5,5, 8,2 ),
	};

	return std::make_shared<TestCaseMap>( lines,
			"example",
R"(1.1....11.
.111...2..
..2.1.111.
...1.2.2..
.112313211
...1.2....
..1...1...
.1.....1..
1.......1.
222111....
)" );
}



std::shared_ptr<TestCaseDangerousPoints> createTestCase10()
{
	// all lines from the example without the last one which is invalid
	std::vector<HydrothermalVentingLine> lines = {
			HydrothermalVentingLine( 0,9, 5,9 ),
			HydrothermalVentingLine( 8,0, 0,8 ),
			HydrothermalVentingLine( 9,4, 3,4 ),
			HydrothermalVentingLine( 2,2, 2,1 ),
			HydrothermalVentingLine( 7,0, 7,4 ),
			HydrothermalVentingLine( 6,4, 2,0 ),
			HydrothermalVentingLine( 0,9, 2,9 ),
			HydrothermalVentingLine( 3,4, 1,4 ),
			HydrothermalVentingLine( 0,0, 8,8 ),
			HydrothermalVentingLine( 5,5, 8,2 ),
	};

	return std::make_shared<TestCaseDangerousPoints>( lines,
			"example dangerous points",
R"((0, 9) -> 2
(1, 9) -> 2
(2, 2) -> 2
(2, 9) -> 2
(3, 4) -> 2
(4, 4) -> 3
(5, 3) -> 2
(5, 5) -> 2
(6, 4) -> 3
(7, 1) -> 2
(7, 3) -> 2
(7, 4) -> 2
)" );
}

int main()
{
	try {

		std::vector<std::shared_ptr<TestCaseBase<std::string>>> test_cases;

		test_cases.push_back( createTestCase1() );
		test_cases.push_back( createTestCase2() );
		test_cases.push_back( createTestCase3() );
		test_cases.push_back( createTestCase4() );
		test_cases.push_back( createTestCase5() );
		test_cases.push_back( createTestCase6() );
		test_cases.push_back( createTestCase7() );
		test_cases.push_back( createTestCase8() );
		test_cases.push_back( createTestCase9() );
		test_cases.push_back( createTestCase10() );

		ColoredOutput co;
		ColBuilder col;
		unsigned idx = 0;

		const int COL_IDX       = col.addCol( "Idx" );
		const int COL_NAME      = col.addCol( "Test" );
		const int COL_TEST_RES  = col.addCol( "Test Result" );

		for( auto & test : test_cases ) {

			idx++;

			col.addColData( COL_IDX, std::to_string(idx) );
			col.addColData( COL_NAME, test->getName() );

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
				std::cout << co.color_output( ColoredOutput::RED, std::string("Exception: ") + error.what() )
						  << std::endl;
				result = "exception";
			} catch( ... ) {
				result = "exception";
			}

			if( result != expected_result ) {
				test_result = co.color_output( ColoredOutput::RED, "failed" );
			} else {
				test_result = co.color_output( ColoredOutput::GREEN, "succeeded" );
			}

			col.addColData( COL_TEST_RES, test_result );

			std::cout << "Result:\n----------------\n" << result
					  << "\n^^^^^^^^^^^^^^^^^^^\n";
			std::cout << "Expedted Result:\n----------------\n" << expected_result
					  << "\n^^^^^^^^^^^^^^^^^^^\n";
			std::cout << "Test case: " <<  test_result
					  << "\n"
					  << "\n\n";
		}

		std::cout << "\n\n"
				  << "Summary:\n"
				  << col.toString() << std::endl;

	} catch( std::exception & error ) {
		std::cout << error.what() << std::endl;
		return 1;
	}

	return 0;
}


#endif /* TEST_TEST_HYDROTHERMALVENTINGLINE_CC_ */

