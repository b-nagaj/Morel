#include "DBManager.hpp"
#include <fstream>

/**
 * gets DB secrets from a local .env file
 * 
 * @return a map containing key/value pairs of secret names & values
 */ 
std::map<std::string, std::string> DBManager::GetDBSecrets() {
    // map to store key/value pairs of DB secrets
    std::map<std::string, std::string> dbSecrets;
    std::string line, key, value;
    std::string pathToEnvFile = "dbSecrets.env";
    std::ifstream envFile(pathToEnvFile);

    if (envFile.is_open()) {
        // read each line from .env file
        // split each line with a delimeter
        // insert each side of the split into a new key/value pair inside dbSecrets
        while ( getline (envFile, line) ) { 
            std::istringstream iss(line);
            std::getline(iss, key, '=');
            std::getline(iss, value);
            dbSecrets.insert({key, value});
        }
        envFile.close();
    }
    else {
        std::cout << "Unable to open environment file";
    }

    return dbSecrets;
}

/**
 * initializes a MySQL connection & authenticates with the database
 * 
 * @return a boolean value based on if the connection was successful/unsuccessful
 */ 
bool DBManager::Connect() {
    // retrieve DB secrets
    std::map<std::string, std::string> dbSecrets = GetDBSecrets();

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
                            stoi(dbSecrets["DB_CLIENT_FLAGS"]))) {
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
 * adds new transactions into the Transactions table
 * 
 * @param newTransactions an array of transactions
 * @param numNewTransactions the number of transactions being added to the DB
 */ 
void DBManager::CreateNewTransactions(Transaction *newTransactions, 
                                      int numNewTransactions) {
    // Create a new transaction
    for (int i = 0; i < numNewTransactions; i++) {
        std::string query = "INSERT INTO Transactions(user_id, amount, category, transaction_date) VALUES ('" +
                            std::to_string(newTransactions[i].GetUserID()) 
                                           + "', '" +
                                           newTransactions[i].GetAmount() 
                                           + "', '" +
                                           newTransactions[i].GetCategory() 
                                           + "', '" +
                                           newTransactions[i].GetDate() 
                                           + "')";
        // execute the query
        if (mysql_query(connection, query.c_str()) != 0) {
            std::cerr << "Error executing SQL query: " 
                      << mysql_error(connection) 
                      << std::endl;
            mysql_close(connection);
        }
    }
}

/**
 * searches for a transaction or transactions matching a specific amount
 * 
 * @param transactionAmount the specific amount to search for
 * @return a result from an executed MySQL query
*/
MYSQL_RES * DBManager::GetTransactionByAmount(std::string transactionAmount) {
    MYSQL_RES * result;

    if (Connect()) {
        // find each transaction that matches the transactionAmount
        std::string query = "SELECT * FROM Transactions WHERE amount = " 
                            + transactionAmount;

        // execute the query
        if (mysql_query(connection, query.c_str()) != 0) {
            std::cerr << "Error executing SQL query: " 
                    << mysql_error(connection) 
                    << std::endl;
        }
        // store the result
        result = mysql_store_result(connection); 
        Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }

    return result;
}

/**
 * Deletes a transaction or transactions
 * 
 * @param transactionID represents a transactions unique identifier
*/
void DBManager::DeleteTransaction(std::string transactionID) {
    if (Connect()) {
        // delete the transaction that matches the transactionID
        std::string query = "DELETE FROM Transactions WHERE transaction_id = "
                            + transactionID;

        // execute the query
        if (mysql_query(connection, query.c_str()) != 0) {
            std::cerr << "Error executing SQL query: " 
                    << mysql_error(connection) 
                    << std::endl;
        }

        Disconnect();
    }
    else {
        std::cout << "\nERROR: Could not connect to database\n\n";
    }
}

/**
 * terminates a MySQL connection
 */ 
void DBManager::Disconnect() {
    mysql_close(connection);
}
