#ifndef DB_MANAGER
#define DB_MANAGER

#include "../entities/Transaction.hpp"
#include "../utils/Date.hpp"
#include "../services/InfisicalService.hpp"

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>
#include <cstring>
#include <mysql/mysql.h>
#include <jsoncpp/json/json.h>

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
        bool Connect();
        void Disconnect();
        bool PrepareQuery(const char * query);
        bool BindParameters(MYSQL_BIND * paramBind, std::string * parameters);
        bool ExecuteQuery();

    public:
        DBManager();
        bool CreateNewTransactions(Transaction *newTransactions, int numNewTransactions);
        int GetNumAffectedRows();
        void SetNumAffectedRows(int numRows);
        bool GetTransactionsByAmount(std::string transactionAmount);
        int GetnumRowsReturned();
        Transaction * StoreFoundTransactions(MYSQL_STMT * stmt, MYSQL_RES * result);
        bool DeleteTransactions(std::string transactionID);
        bool UpdateTransaction(Transaction transaction);
};

#endif
