#ifndef DIALOG_HPP
#define DIALOG_HPP

#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#include "Helper.hpp"

class Dialog : public Helper{

    public:

        int option;
        const int NUM_MENU_OPTIONS = 4;
        std::ifstream inputFile;

        Dialog();
        void Menu();
        void WelcomeBanner();
        bool ValidateChoice(std::string c);
        void ReportBanner(std::ostream& stream);

};

#endif