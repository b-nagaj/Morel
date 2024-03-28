#ifndef DB_MANAGER
#define DB_MANAGER

#include "../entities/Transaction.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <mysql/mysql.h>

class DBManager {
    // attributes
    private:
        MYSQL *connection;

    //methods
    private:
        std::map<std::string, std::string> GetDBSecrets();
    public:
        bool Connect();
        void CreateNewTransactions(Transaction *newTransactions, int numNewTransactions);
        MYSQL_RES * GetTransactionByAmount(std::string transactionAmount);
        void DeleteTransaction(int transactionAmount);
        void Disconnect();
};

#endif
