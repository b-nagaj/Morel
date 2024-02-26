#include "DBManager.hpp"

std::map<std::string, std::string> DBManager::GetDBSecrets() {
    std::map<std::string, std::string> dbSecrets;
    std::string line, key, value;
    std::ifstream envFile ("/Users/bryce/Documents/GitHub/Projects/Morel/dbSecrets.env");

    if (envFile.is_open()) {
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
    if (!mysql_real_connect(connection, dbSecrets["DB_HOST"].c_str(), dbSecrets["DB_USER"].c_str(), dbSecrets["DB_PASSWORD"].c_str(), dbSecrets["DB_NAME"].c_str(), stoi(dbSecrets["DB_PORT"]), dbSecrets["DB_SOCKET"].c_str(), stoi(dbSecrets["DB_CLIENT_FLAGS"]))) {
        std::cerr << "Error connecting to MySQL database: " << mysql_error(connection) << std::endl;
        mysql_close(connection);
        return false;
    }
    else {
        return true;
    }
}

void DBManager::CreateNewTransactions(Transaction *newTransactions, int numNewTransactions) {
    // execute INSERT queries for each new transaction
    for (int i = 0; i < numNewTransactions; i++) {
        std::string query = "INSERT INTO Transactions(user_id, amount, category, transaction_date) VALUES ('" +
                            std::to_string(newTransactions[i].GetUserID()) + "', '" +
                            newTransactions[i].GetAmount() + "', '" +
                            newTransactions[i].GetCategory() + "', '" +
                            newTransactions[i].GetTransactionDate() + "')";
        // handle exceptions
        if (mysql_query(connection, query.c_str()) != 0) {
            std::cerr << "Error executing SQL query: " << mysql_error(connection) << std::endl;
            mysql_close(connection);
        }
    }
}

void DBManager::Disconnect() {
    mysql_close(connection);
}
