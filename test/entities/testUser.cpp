#define BOOST_TEST_MODULE "User"
#include <boost/test/included/unit_test.hpp>

#include "../../src/entities/User.hpp"
#include "../../src/entities/User.cpp"

BOOST_AUTO_TEST_SUITE ( userTestSuite )

    BOOST_AUTO_TEST_CASE( testUserInitialization ) {
        User user("testUsername");
        std::string username = user.GetUsername();
        BOOST_CHECK_EQUAL(username, "testUsername");
    }   

BOOST_AUTO_TEST_SUITE_END()