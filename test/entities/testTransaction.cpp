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
        BOOST_CHECK_EQUAL(transaction.GetTransactionDate(), "0000-00-00 00:00:00");
    }

BOOST_AUTO_TEST_SUITE_END()
