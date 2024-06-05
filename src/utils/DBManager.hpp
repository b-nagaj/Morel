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
        int numRowsReturned;
        const int STRING_SIZE = 50;
        Transaction transactions[50];

    public:
        MYSQL_STMT * stmt;
        MYSQL_RES * result;

    //methods
    private:
        std::map<std::string, std::string> GetDBSecrets();
        bool Connect();
        void Disconnect();


    public:
        DBManager();
        int CreateNewTransactions(Transaction *newTransactions, int numNewTransactions);
        int GetNumAffectedRows();
        bool GetTransactionByAmount(std::string transactionAmount);
        int GetnumRowsReturned();
        Transaction * StoreFoundTransaction(MYSQL_STMT * stmt, MYSQL_RES * result);
        void DeleteTransaction(std::string transactionID);
};

#endif
