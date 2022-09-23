#define BOOST_TEST_MODULE dialog
#include <boost/test/included/unit_test.hpp>

#include "../lib/Helper.hpp"
#include "../src/Helper.cpp"
#include "../lib/Dialog.hpp"
#include "../src/Dialog.cpp"

BOOST_AUTO_TEST_SUITE ( dialogTestSuite );

    BOOST_AUTO_TEST_CASE ( constructor ) {

        Dialog d;    

        BOOST_CHECK_EQUAL ( d.username, "" );
        BOOST_CHECK_EQUAL ( d.option, 0 );

    }

    BOOST_AUTO_TEST_CASE ( validateChoice ) {

        Dialog d;
        Dialog d2;
        std::string choice1 = std::to_string(d.NUM_MENU_OPTIONS - (d.NUM_MENU_OPTIONS - 1)); 
        std::string choice2 = std::to_string(d.NUM_MENU_OPTIONS + 1); 

        std::cout.rdbuf(NULL);
        bool validChoice;
        validChoice = d.ValidateChoice(choice1);

        bool invalidChoice;
        invalidChoice = d.ValidateChoice(choice2);

        BOOST_CHECK_EQUAL ( validChoice, true );
        BOOST_CHECK_EQUAL ( invalidChoice, false );

    }

BOOST_AUTO_TEST_SUITE_END()