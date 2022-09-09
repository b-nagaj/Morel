#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#pragma once

class Dialog {

    public:

        std::string username;
        int option;
        std::ifstream inputFile;

        Dialog();
        void Menu();
        void WelcomeBanner();
        void GetUsername();
        bool ValidateChoice(std::string c);
        void ReportBanner(std::ostream& stream);

};