#ifndef INFISICAL_SERVICE
#define INFISICAL_SERVICE

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <curl/curl.h>

class InfisicalService {
    // methods
    public:
        std::map<std::string, std::string> GetSecrets();
        std::string Authenticate();
        std::string GetDBSecrets(std::string token);
};

#endif
