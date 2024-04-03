#ifndef DB_MANAGER
#define DB_MANAGER

#include "../entities/Transaction.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <cstring>
#include <mysql/mysql.h>

class DBManager {
    // attributes
    private:
        MYSQL * connection;
        MYSQL_STMT * stmt;
        MYSQL_BIND bind[4];
        const int STRING_SIZE = 50;

    //methods
    private:
        std::map<std::string, std::string> GetDBSecrets();
    public:
        bool Connect();
        void CreateNewTransactions(Transaction *newTransactions, int numNewTransactions);
        MYSQL_RES * GetTransactionByAmount(std::string transactionAmount);
        void DeleteTransaction(std::string transactionID);
        void Disconnect();
};

#endif
