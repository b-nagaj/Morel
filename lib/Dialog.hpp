#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#pragma once

class Dialog {

    public:

        int option;
        std::string errorMessage;

        Dialog();
        void WelcomeBanner();
        void Menu();
        bool ValidateChoice(std::string c);
        void ReportBanner(std::ostream& stream);

};