#define BOOST_TEST_MODULE setup
#include <boost/test/included/unit_test.hpp>

#include "../lib/Setup.hpp"
#include "../src/Setup.cpp"

BOOST_AUTO_TEST_SUITE ( setupTestSuite )

BOOST_AUTO_TEST_CASE ( testCase1 ) {
    BOOST_CHECK_EQUAL(2+2, 4);
}

// BOOST_AUTO_TEST_CASE(test2) {
//     BOOST_CHECK_EQUAL(2*2, 4);
// }

BOOST_AUTO_TEST_SUITE_END()