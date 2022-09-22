#define BOOST_TEST_MODULE helper
#include <boost/test/included/unit_test.hpp>

#include "../lib/Calculator.hpp"
#include "../src/Calculator.cpp"
#include "../lib/Helper.hpp"
#include "../src/Helper.cpp"
#include "../lib/Dialog.hpp"
#include "../src/Dialog.cpp"
#include "../lib/UpdateExpenseList.hpp"
#include "../src/UpdateExpenseList.cpp"
#include "../lib/GenerateDataFile.hpp"
#include "../src/GenerateDataFile.cpp"
#include "../lib/GenerateReport.hpp"
#include "../src/GenerateReport.cpp"

#include <string>

BOOST_AUTO_TEST_SUITE ( calculatorTestSuite )

    BOOST_AUTO_TEST_CASE ( prompt ) {

        Calculator d;

        const int NUM_MENU_OPTIONS = 4;
        std::string messages [NUM_MENU_OPTIONS];
        for (int i = 0; i < NUM_MENU_OPTIONS; i++) {
            std::string message = "Menu option " + std::to_string(i + 1) + " selected";
            messages[i] = message; 
        }

        std::string message = "";
        for (int i = 1; i < 5; i++) {
            d.myDialog.option = i;

            switch (d.myDialog.option) {
            case 1 :
                message = messages[0];
                break;

            case 2 : 
                message = messages[1];
                break;

            case 3 :
                message = messages[2];
                break;
        
            case 4 :
                message = messages[3];
            }

            if ( d.myDialog.option == 1 ) {
                BOOST_CHECK_EQUAL ( message, messages[0] );
            }
            else if ( d.myDialog.option == 2 ) {
                BOOST_CHECK_EQUAL ( message, messages[1] );
            }
            else if ( d.myDialog.option == 3 ) {
                BOOST_CHECK_EQUAL ( message, messages[2] );
            }
            else {
                BOOST_CHECK_EQUAL ( message, messages[3] );
            }
        }

    }

BOOST_AUTO_TEST_SUITE_END()