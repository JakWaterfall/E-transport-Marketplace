#include <boost/test/unit_test.hpp>

/////////////////////////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_SUITE( MyTestSuiteExample )

BOOST_AUTO_TEST_CASE( ThisExampleTest )
{
    int a,b = 2; //
    // here you would have the expected output, and the function call which should produce said output
    BOOST_CHECK_EQUAL(a, b);
}

BOOST_AUTO_TEST_SUITE_END()

/////////////////////////////////////////////////////////////////////////////////////////
