#define BOOST_TEST_MODULE helper
#include <boost/test/included/unit_test.hpp>

#include "../lib/Calculator.hpp"
#include "../src/Calculator.cpp"
#include "../lib/Helper.hpp"
#include "../src/Helper.cpp"
#include "../lib/Dialog.hpp"
#include "../src/Dialog.cpp"
#include "../lib/ExpenseListUpdater.hpp"
#include "../src/ExpenseListUpdater.cpp"
#include "../lib/DataFileGenerator.hpp"
#include "../src/DataFileGenerator.cpp"
#include "../lib/TransactionAdder.hpp"
#include "../src/TransactionAdder.cpp"
#include "../lib/TransactionDeleter.hpp"
#include "../src/TransactionDeleter.cpp"
#include "../lib/ReportGenerator.hpp"
#include "../src/ReportGenerator.cpp"

#include <string>

BOOST_AUTO_TEST_SUITE ( calculatorTestSuite )

    BOOST_AUTO_TEST_CASE ( prompt ) {

        Calculator d;

        std::string messages [d.myDialog.NUM_MENU_OPTIONS];
        for (int i = 0; i < d.myDialog.NUM_MENU_OPTIONS; i++) {
            std::string message = "Menu option " + std::to_string(i + 1) + " selected";
            messages[i] = message; 
        }

        std::string message = "";
        for (int i = 1; i < (d.myDialog.NUM_MENU_OPTIONS + 1); i++) {
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
                break;

            case 5 :
                message = messages[4];
                break;
            
            case 6 :
                message = messages[5];
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
            else if ( d.myDialog.option == 4 ) {
                BOOST_CHECK_EQUAL ( message, messages[3] );
            }
            else if (d.myDialog.option == 5 ) {
                BOOST_CHECK_EQUAL ( message, messages[4] );
            }
            else {
                BOOST_CHECK_EQUAL( message, messages[5] );
            }
        }

    }

BOOST_AUTO_TEST_SUITE_END()