#define BOOST_TEST_MODULE helper
#include <boost/test/included/unit_test.hpp>

#include "../lib/Helper.hpp"
#include "../src/Helper.cpp"

BOOST_AUTO_TEST_SUITE ( helperTestSuite )

    BOOST_AUTO_TEST_CASE ( getUsername ) {

        Helper h;

        h.inputFile.open("test/testConfig.txt"); 
        std::getline(h.inputFile, h.username);
        h.inputFile.close();
        std::string testUsername = "testUsername";

        BOOST_CHECK_EQUAL ( h.username, testUsername );

    }

    BOOST_AUTO_TEST_CASE ( getPaths ) {

        Helper h;

        std::string lines [3];

        h.inputFile.open("test/testConfig.txt");

        int i = 0;
        while (i < 3) {
            std::getline(h.inputFile, lines[i], '\n');
            i++;
        }

        if (lines[1].back() != '/') {
            h.dataFilesPath = lines[1] + "/";
        }
        else {
            h.dataFilesPath = lines[1];
        }

        if (lines[2].back() != '/') {
            h.reportFilesPath = lines[2] + "/";
        }
        else {
            h.reportFilesPath = lines[2];
        }

        h.inputFile.close();
        std::string testDataFilesPath = "/test/data/path/";
        std::string testReportFilesPath = "/test/reports/path";

        BOOST_CHECK_EQUAL ( h.dataFilesPath, testDataFilesPath );
        BOOST_CHECK_NE ( h.reportFilesPath, testReportFilesPath );
        BOOST_CHECK_EQUAL ( h.reportFilesPath, (testReportFilesPath + "/") );

    }

    BOOST_AUTO_TEST_CASE ( validateMonth ) {

        Helper h;
        Helper h2;

        bool validMonth = false;
        bool invalidMonth = true;
        h.month = "January";
        h2.month = "Jan";

        for (int i = 0; i < 24; i++) {
            if (h.validMonths[i] == h.month) {
                validMonth = true;
                break;
            }
            if (h.validMonths[i] == h2.month) {
                invalidMonth = false;
            }
        }

        BOOST_CHECK_EQUAL ( validMonth, true );
        BOOST_CHECK_EQUAL ( invalidMonth, true );

    }

    BOOST_AUTO_TEST_CASE ( getExpenses ) {

        Helper h;

        h.inputFile.open("test/testConfig.txt");

        for (int i = 0; i < 3; i++) {
            std::getline(h.inputFile, h.expense);
        }

        h.numExpenses = 0;
        if (h.inputFile) {
            while (h.expense != "" && h.numExpenses < 20) {
                std::getline(h.inputFile, h.expense);
                h.expenses[h.numExpenses] = h.expense;
                h.numExpenses++;
            }
            h.numExpenses--;
        }

        h.inputFile.close();

        std::string testExpense;
        for (int i = 0; i < h.numExpenses; i++) {
            testExpense = "testExpense" + std::to_string(i);
            BOOST_CHECK_EQUAL ( h.expenses[i], testExpense );
        }

    }

BOOST_AUTO_TEST_SUITE_END()

