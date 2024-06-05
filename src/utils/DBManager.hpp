#ifndef DB_MANAGER
#define DB_MANAGER

#include "../entities/Transaction.hpp"
#include "../utils/Date.hpp"

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
        int numQueryParams;
        int numAffectedRows;
        int numRows;
        const int STRING_SIZE = 50;
        Transaction transactions[50];

    public:
        MYSQL_STMT * stmt;
        MYSQL_RES * result;

    //methods
    private:
        std::map<std::string, std::string> GetDBSecrets();

    public:
        DBManager();
        bool Connect();
        int CreateNewTransactions(Transaction *newTransactions, int numNewTransactions);
        int GetNumAffectedRows();
        int GetNumRows();
        bool GetTransactionByAmount(std::string transactionAmount);
        Transaction * StoreFoundTransaction(MYSQL_STMT * stmt, MYSQL_RES * result);
        void DeleteTransaction(std::string transactionID);
        void Disconnect();
};

#endif
