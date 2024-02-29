#include <boost/test/unit_test.hpp>

#include "../../src/entities/Transaction.hpp"
#include "../../src/entities/Transaction.cpp"
#include "../../src/utils/Date.hpp"
#include "../../src/utils/Date.cpp"

BOOST_AUTO_TEST_SUITE ( transactionTestSuite )

    BOOST_AUTO_TEST_CASE( defaultTransactionContructor ) {
        Transaction transaction;

        BOOST_CHECK_EQUAL(transaction.GetUserID(), 0);
        BOOST_CHECK_EQUAL(transaction.GetAmount(), "");
        BOOST_CHECK_EQUAL(transaction.GetCategory(), "");
        // validate that the transactionDate was converted to a timestamp
        BOOST_CHECK_EQUAL(transaction.GetTransactionDate(), "0000-00-00 00:00:00");
    }

    BOOST_AUTO_TEST_CASE( alternateTransactionContructor ) {
        int userID = 1;
        Date date(2, 28, 2024); // initialize a new 'Date' object
        std::string amount = "1000.00";
        std::string category = "testCategory";

        Transaction transaction(1, "1000.00", "testCategory", date);

        BOOST_CHECK_EQUAL(transaction.GetUserID(), 1);
        BOOST_CHECK_EQUAL(transaction.GetAmount(), "1000.00");
        BOOST_CHECK_EQUAL(transaction.GetCategory(), "testCategory");
        BOOST_CHECK_EQUAL(transaction.GetTransactionDate(), "2024-02-28 00:00:00");
    }

BOOST_AUTO_TEST_SUITE_END()
