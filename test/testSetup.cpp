#define BOOST_TEST_MODULE setup
#include <boost/test/included/unit_test.hpp>

#include <fstream>
#include <string>
#include <boost/filesystem.hpp>

#include "../lib/Setup.hpp"
#include "../src/Setup.cpp"

BOOST_AUTO_TEST_SUITE ( setupTestSuite );

    BOOST_AUTO_TEST_CASE ( constructor ) {

        std::cout.rdbuf(NULL);
        Setup s;

        BOOST_CHECK_EQUAL( s.expense, "" );
        BOOST_CHECK_EQUAL( s.numExpenses, 0 );
        BOOST_CHECK_EQUAL( s.username, "" );
        BOOST_CHECK_EQUAL( s.dataFilesPath, "" );
        BOOST_CHECK_EQUAL( s.reportFilesPath, "" );

    }

    BOOST_AUTO_TEST_CASE ( validatePaths ) {

        std::cout.rdbuf(NULL);
        Setup s;
        s.dataFilesPath = "/home/bryce/Desktop";
        s.reportFilesPath = "/home/bryce/Documents";

        bool validPath;
        validPath = s.ValidatePaths();

        BOOST_CHECK_EQUAL( validPath, true );

        Setup s2;
        s2.dataFilesPath = "/not/a/real/data/path";
        s2.reportFilesPath = "/not/a/real/reports/path";

        std::cout.rdbuf(NULL);
        validPath = s2.ValidatePaths();

        BOOST_CHECK_EQUAL( validPath, false );

    }

    BOOST_AUTO_TEST_CASE ( write ) {

        std::cout.rdbuf(NULL);
        Setup s;
        s.numExpenses = 3;
        s.username = "testUsername";
        s.dataFilesPath = "/test/data/path/";
        s.reportFilesPath = "/test/reports/path";
        for (int i = 0; i < s.numExpenses; i++) {
            s.expense = "testExpense" + std::to_string(i);
            s.expenses[i] = s.expense;
        }

        std::ofstream outputFile;
        outputFile.open("test/testConfig.txt");

        if (outputFile) {
            outputFile << s.username << std::endl
                    << s.dataFilesPath << std::endl
                    << s.reportFilesPath << std::endl;
            
            for (int i = 0; i < s.numExpenses; i++) {
                outputFile << s.expenses[i] << std::endl;
            }
            outputFile.close();
        }
        else {
            outputFile.close();
        }

        std::ifstream inputFile;
        inputFile.open("test/testConfig.txt");

        std::string lines [s.numExpenses + 3];
        if (inputFile) {
            for (int i = 0; i < (s.numExpenses + 3); i++) {
                std::getline(inputFile, lines[i]);
            }
            inputFile.close();
        }

        BOOST_CHECK_EQUAL( s.username, lines[0] );
        BOOST_CHECK_EQUAL( s.dataFilesPath, lines[1] );
        BOOST_CHECK_EQUAL( s.reportFilesPath, lines[2] );
        for (int i = 0; i < s.numExpenses; i++) {
            BOOST_CHECK_EQUAL( s.expenses[i], lines[i + 3] );
        }

    }

BOOST_AUTO_TEST_SUITE_END()