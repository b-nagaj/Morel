#include "InfisicalService.hpp"

/**
 * gets secrets from a local .env file
 * 
 * @return a map containing key/value pairs of secret names & values
 */ 
std::map<std::string, std::string> InfisicalService::GetSecrets() {
    // map to store key/value pairs of secrets
    std::map<std::string, std::string> secrets;
    std::string line;
    std::string key;
    std::string value;
    std::string pathToEnvFile = "secrets.env";
    std::ifstream envFile(pathToEnvFile);

    if (envFile.is_open()) {
        // read each line from .env file
        // split each line with a delimeter
        // insert each side of the split into a new key/value pair
        while ( getline (envFile, line) ) { 
            std::istringstream iss(line);
            std::getline(iss, key, '=');
            std::getline(iss, value);
            secrets.insert({key, value});
        }
        envFile.close();
    }
    else {
        std::cout << "Unable to open environment file"
                  << "\nEmail bryce.nagaj@gmail.com for help configuring a local .env file";
    }

    return secrets;
}

/**
 * Handles responses from the server when hitting Infisical endpoints
 */
size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *response)
{
    response->append((char *)contents, size * nmemb);
    return size * nmemb;
}

/**
 * Handles authentication with the Infisical API service in order to recieve an
 * access token
 * 
 * @param
 */ 
std::string InfisicalService::Authenticate() {
    std::map<std::string, std::string> secrets = GetSecrets();
    std::string clientID = secrets["CLIENT_ID"].c_str();
    std::string clientSecret = secrets["CLIENT_SECRET"].c_str();

    CURL* curl;
    CURLcode res;
    std::string response;

    // initialize curl session
    curl = curl_easy_init();
    if (curl) {
        // set the URL for the POST request
        curl_easy_setopt(curl, CURLOPT_URL, "https://app.infisical.com/api/v1/auth/universal-auth/login");

        // set the content type header
        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/x-www-form-urlencoded");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // specify the POST data
        std::string postFields = "clientId=c4028deb-324d-4fb7-9f3a-26f79c3f8fe2&clientSecret=687ba4d072363ae6635f7f95e27dc98993aef5b74b5c6557e062e3445355e302";
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields.c_str());

        // set up callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // perform the POST request
        res = curl_easy_perform(curl);

        // check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 

        // clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } 
    else {
        std::cerr << "Failed to initialize curl." << std::endl;
        return "Error";
    }

    return response;
}

std::string InfisicalService::GetDBSecrets(std::string token) {
    CURL* curl;
    CURLcode res;
    std::string response;

    // initialize curl session
    curl = curl_easy_init();
    if (curl) {
        // set the URL for the POST request
        curl_easy_setopt(curl, CURLOPT_URL, "https://app.infisical.com/api/v3/secrets/raw?workspaceId=0f92f205-9682-4545-b3d4-306789c057f7&environment=dev");

        // set the content type header
        struct curl_slist* headers = NULL;
        std::string authorizationHeader = "Authorization: Bearer " + token;
        headers = curl_slist_append(headers, authorizationHeader.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        // set up callback function to capture the response
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        // perform the POST request
        res = curl_easy_perform(curl);

        // check for errors
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        } 

        // clean up
        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } 
    else {
        std::cerr << "Failed to initialize curl." << std::endl;
        return "Error";
    }

    return response;
}
