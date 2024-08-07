#include "DBManager.hpp"

/**
 * Initializes # of query parameters
*/
DBManager::DBManager() {
    connection = nullptr;
    numQueryParams = 0;
    numAffectedRows = 0;
    numRowsReturned = 0;
    stmt = nullptr;
    result = nullptr;
}

/**
 * initializes a MySQL connection & authenticates with the database
 * 
 * @return a boolean value based on if the connection was successful/unsuccessful
 */ 
bool DBManager::Connect() {
    // retrieve client ID & client secret for Infisical
    InfisicalService infisicalService;
    std::map<std::string, std::string> secrets = infisicalService.GetSecrets();
    std::string response = "";

    // retrieve an auth token from Infisical
    response = infisicalService.Authenticate();
    
    // parse the response containing the access token
    Json::Value outputAsJson;
    Json::CharReaderBuilder readerBuilder;
    std::string err;
    const std::unique_ptr<Json::CharReader> reader(readerBuilder.newCharReader());

    // extract the access token from the response
    std::string accessToken;
    if (reader->parse(response.c_str(), response.c_str() + response.length(), &outputAsJson, &err)) {
        accessToken = outputAsJson["accessToken"].asString();
    }
    else {
        std::cout << "\nCould not retrieve access token";
        return false;
    }

    // retrieve the DB secrets
    response = infisicalService.GetDBSecrets(accessToken);

    // parse the response
    reader->parse(response.c_str(), response.c_str() + response.length(), &outputAsJson, &err);

    // extract the list of secrets
    Json::Value listOfDBSecrets = outputAsJson["secrets"];

    // extract each secretKey & secretValue from the list of DB secrets
    std::map<std::string, std::string> dbSecrets;
    for (Json::Value::ArrayIndex i = 0; i < listOfDBSecrets.size(); i++) {
        Json::Value secret = listOfDBSecrets[i];
        std::string secretName = secret["secretKey"].asString();
        std::string secretValue = secret["secretValue"].asString();

        // store the secrets
        dbSecrets.insert({secretName, secretValue});
    }

    // establish a MySQL connection & report connection exceptions
    connection = mysql_init(NULL);
    if (connection == NULL) {
        std::cerr << "Error initializing MySQL connection" << std::endl;
        return false;
    }
    
    // authenticate with database
    if (!mysql_real_connect(connection, 
                            dbSecrets["DB_HOST"].c_str(), 
                            dbSecrets["DB_USER"].c_str(), 
                            dbSecrets["DB_PASSWORD"].c_str(), 
                            dbSecrets["DB_NAME"].c_str(), 
                            stoi(dbSecrets["DB_PORT"]), 
                            dbSecrets["DB_SOCKET"].c_str(), 
                            std::stoi(dbSecrets["DB_CLIENT_FLAGS"]))) {
        std::cerr << "Error connecting to MySQL database: " 
                  << mysql_error(connection) 
                  << std::endl;
        mysql_close(connection);
        return false;
    }
    else {
        return true;
    }
}

/**
 * terminates a MySQL connection
 */ 
void DBManager::Disconnect() {
    mysql_close(connection);
}

/**
 * adds new transactions into the Transactions table
 * 
 * @param newTransactions an array of transactions
 * @param numNewTransactions the number of transactions being added to the DB
 */ 
bool DBManager::CreateNewTransactions(Transaction *newTransactions, 
                                      int numNewTransactions) {
    if (Connect()) {
        // Create a new transaction
        for (int i = 0; i < numNewTransactions; i++) {
            std::string userID = std::to_string(newTransactions[i].GetUserID());
            std::string amount = newTransactions[i].GetAmount();
            std::string category = newTransactions[i].GetCategory();
            std::string date = newTransactions[i].GetDate();

            // define the INSERT query
            const char * query = "INSERT INTO Transactions(user_id, amount, category, transaction_date) \
                            VALUES (?, ?, ?, ?)";

            // prepare the INSERT query
            if (!PrepareQuery(query)) {
                return false;
            }

            // bind parameter data
            numQueryParams = 4;
            MYSQL_BIND paramBind[numQueryParams];
            std::string parameters[numQueryParams];
            parameters[0] = userID;
            parameters[1] = amount;
            parameters[2] = category;
            parameters[3] = date;
            memset(paramBind, 0, sizeof(paramBind));
            if (!BindParameters(paramBind, parameters)) {
                return false;
            }

            // execute the query
            if (!ExecuteQuery()) {
                return false;
            }

            // get # of affected rows
            numAffectedRows += mysql_stmt_affected_rows(stmt); 

            // free the statement
            if (mysql_stmt_close(stmt)) {
                std::cout << "\nERROR: Failed to free the INSERT statement";
                std::cout << "\n" << mysql_error(connection) << "\n\n";
                return false;
            }
        }
        
        Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database";
        std::cout << "\n" << mysql_error(connection) << "\n\n";
    }

    return true;
}

/* 
 * returns the number of rows affected by an INSERT/DELETE/UPDATE query
 *
 * @return numAffectedRows
*/
int DBManager::GetNumAffectedRows() {
    return numAffectedRows;
}

/**
 * sets the number of rows affected by an INSERT/DELETE/UPDATE query
 * 
 * @param numRows
 */
void DBManager::SetNumAffectedRows(int numRows) {
    numAffectedRows = numRows;
}

/*
 * prepares a query statement
 *
 * @param query
 * @return boolean value that represents success/failure
*/
bool DBManager::PrepareQuery(const char * query) {
    stmt = mysql_stmt_init(connection);
    if (!stmt) {
        std::cout << "\nERROR: Could not prepare the SQL statement, "
                  << "out of memory\n\n";
        std::cout << "\n" << mysql_stmt_error(stmt) << "\n\n";
        return false;
    }
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        std::cout << "\nERROR: Could not prepare the SQL statement";
        std::cout << "\n" << mysql_stmt_error(stmt) << "\n\n";
        return false;
    }

    return true;
}

/*
 * binds parameter data for a prepared SQL statement
 * 
 * @param a pointer to an array of MYSQL_BIND parameters
 * @param a pointer to an string array of parameter data
 * @return boolean value that represents success/failure
*/
bool DBManager::BindParameters(MYSQL_BIND * paramBind, std::string * parameters) {
    for (int i = 0; i < numQueryParams; i++) {
        paramBind[i].buffer_type = MYSQL_TYPE_STRING;
        paramBind[i].buffer = const_cast<char *>(parameters[i].c_str());
        paramBind[i].buffer_length = STRING_SIZE;
        paramBind[i].is_null = 0;
    }

    if (mysql_stmt_bind_param(stmt, paramBind)) {
        std::cout << "\nERROR: Could not prepare the SQL statement, "
                  << "the buffers could not be bound";
        std::cout << "\n" << mysql_stmt_error(stmt) << "\n\n";
        return false;
    };

    return true;
}

/*
 * executes a prepared SQL statement
 * 
 * @return boolean value that represents success/failure
*/
bool DBManager::ExecuteQuery() {
    if (mysql_stmt_execute(stmt)) {
        std::cout << "\nERROR: SQL statement execution has failed";
        std::cout << "\n" << mysql_stmt_error(stmt);
        return false;
    }

    return true;
}

/**
 * searches for transactions in the Transactions table that match a specific amount
 * 
 * @param transactionAmount the specific amount to search for
 * @return a result from an executed MySQL query
*/
bool DBManager::GetTransactionsByAmount(std::string transactionAmount) {
    if (Connect()) {
        // define the SELECT query
        const char * query = "SELECT * FROM Transactions WHERE amount = ?";

        // Prepare the SELECT query
        if (!PrepareQuery(query)) {
            return false;
        }

        // bind parameter data
        numQueryParams = 1;
        MYSQL_BIND paramBind[numQueryParams];
        std::string parameters[numQueryParams];
        memset(paramBind, 0, sizeof(paramBind));
        parameters[0] = transactionAmount;
        if (!BindParameters(paramBind, parameters)) {
            return false;
        }

        // execute the SELECT statement
        if (!ExecuteQuery()) {
            return false;
        }

        // store the result
        result = mysql_stmt_result_metadata(stmt);
        if (!result) {
            std::cout << "\nERROR: no meta information was returned";
            std::cout << "\n" << mysql_stmt_error(stmt);
            return false;
        }

        // invoke the StoreFoundTransactions() function to store the result
        StoreFoundTransactions(stmt, result);

        // check that matching transactions were found
        if (numRowsReturned > 0) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        std::cout << "\nERROR: Could not connect to database";
        std::cout << "\n" << mysql_error(connection) << "\n\n";
        return false;
    }
}

/*
* stores the result set that's captured by GetTransactionsByAmount()
*
* @param stmt the statement that was used to execute the SELECT query from
* GetTransactionsByAmount();
* @param a pointer to an array of Transaction objects containing result data
*/
Transaction * DBManager::StoreFoundTransactions(MYSQL_STMT * stmt, MYSQL_RES * result) {
    // column data
    int transaction_id;
    int user_id;
    double amount;
    char category[51];
    MYSQL_TIME transaction_date;

    // bind result data
    int numQueryResultColumns = 5;
    MYSQL_BIND resultBind[numQueryResultColumns];
    memset(resultBind, 0, sizeof(resultBind));

    // transaction_id
    resultBind[0].buffer_type = MYSQL_TYPE_LONG;
    resultBind[0].buffer = (char *)&transaction_id;
    resultBind[0].buffer_length = sizeof(int);
    resultBind[0].is_null = 0; 

    // user_id
    resultBind[1].buffer_type = MYSQL_TYPE_LONG;
    resultBind[1].buffer = (char *)&user_id;
    resultBind[1].buffer_length = sizeof(int);
    resultBind[1].is_null = 0;

    // amount
    resultBind[2].buffer_type = MYSQL_TYPE_DOUBLE;
    resultBind[2].buffer = (char *)&amount;
    resultBind[2].buffer_length = sizeof(double);
    resultBind[2].is_null = 0; 

    // category
    resultBind[3].buffer_type = MYSQL_TYPE_STRING;
    resultBind[3].buffer = (char *)&category;
    resultBind[3].buffer_length = 51;
    resultBind[3].is_null = 0;

    // transaction_date
    resultBind[4].buffer_type = MYSQL_TYPE_TIMESTAMP;
    resultBind[4].buffer = (char *)&transaction_date;
    resultBind[4].buffer_length = sizeof(MYSQL_TIME);
    resultBind[4].is_null = 0;

    if (mysql_stmt_bind_result(stmt, resultBind)) {
        std::cout << "\nERROR: mysql_store_result() failed"
                  << "\n" << mysql_stmt_error(stmt);
    }

    // store the result
    mysql_stmt_store_result(stmt);

    // Fetch the row(s) to print the result data
    numRowsReturned = mysql_stmt_num_rows(stmt);
    if (numRowsReturned > 0) {   
        int status;
        int i = 0;
        while ((status = mysql_stmt_fetch(stmt)) == 0) {
            // format the transaction amount data into a string
            std::ostringstream strs;
            strs << amount;
            std::string amountStr = strs.str();

            // format the transaction category data into a string
            std::string categoryStr(category);

            // instantiate a new Date object based on the transaction's timestamp data
            Date date(transaction_date.month, 
                      transaction_date.day, 
                      transaction_date.year); 

            // instantiate a new Transaction object for the row
            Transaction transaction(user_id, 
                                    amountStr, 
                                    categoryStr, 
                                    date);

            // store the transaction's ID
            transaction.SetTransactionID(transaction_id);

            // add the new transaction to the list of all matching transactions
            transactions[i] = transaction;
            i++;
        }
    }
    else {
        std::cout << "\n0 transactions matching that amount were found\n\n";
    }

    return transactions;
}

/*
 * returns the number of rows retrieved from a SELECT query
 *
 * @return numRowsReturned
*/
int DBManager::GetnumRowsReturned() {
    return numRowsReturned;
}

/*
 * Deletes a transaction or transactions
 * 
 * @param transactionID represents a transactions unique identifier
 * @return the success/failure of the deletion
*/
bool DBManager::DeleteTransactions(std::string transactionID) {
    if (Connect()) {
        // define the DELETE query
        const char * query = "DELETE FROM Transactions WHERE transaction_id = ?";

        // prepare the DELETE query
        if (!PrepareQuery(query)) {
            return false;
        }

        // bind parameter data
        numQueryParams = 1;
        MYSQL_BIND paramBind[numQueryParams];
        std::string parameters[numQueryParams];
        parameters[0] = transactionID;
        memset(paramBind, 0, sizeof(paramBind));
        if (!BindParameters(paramBind, parameters)) {
            return false;
        }

        // execute the query
        if (!ExecuteQuery()) {
            return false;
        }

        // disconnect the session & free the statement/result
        Disconnect();
        mysql_stmt_free_result(stmt);
        mysql_free_result(result);
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n";
        return false;
    }

    return true;
}

/**
 * Updates a transaction
 *
 * @param transaction a Transaction entity that represents the transaction to update
 * @return the success/failure of the update
 */
bool DBManager::UpdateTransaction(Transaction transaction) {
    if (Connect()) {
        std::string amount = transaction.GetAmount();
        std::string category = transaction.GetCategory();
        std::string transactionID = std::to_string(transaction.GetTransactionID());

        // define the UPDATE query
        const char * query = "UPDATE Transactions SET amount = ?, category = ? WHERE transaction_id = ?;";

        // prepare the UPDATE query
        if (!PrepareQuery(query)) {
            return false;
        }

        // bind parameter data
        numQueryParams = 3;
        MYSQL_BIND paramBind[numQueryParams];
        std::string parameters[numQueryParams];
        parameters[0] = amount;
        parameters[1] = category;
        parameters[2] = transactionID;
        memset(paramBind, 0, sizeof(paramBind));
        if (!BindParameters(paramBind, parameters)) {
            return false;
        }

        // execute the query
        if (!ExecuteQuery()) {
            return false;
        }

        // get # of affected rows
        numAffectedRows += mysql_stmt_affected_rows(stmt); 

        // free the statement
        if (mysql_stmt_close(stmt)) {
            std::cout << "\nERROR: Failed to free the UPDATE statement";
            std::cout << "\n" << mysql_error(connection) << "\n\n";
            return false;
        }

        Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database";
        std::cout << "\n" << mysql_error(connection) << "\n\n";
    }

    return true;
}
