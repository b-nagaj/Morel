#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#include "../lib/Calculator.hpp"

#pragma once

class Dialog {

    public:

        int option;
        Calculator myCalculator;

        Dialog();
        void WelcomeBanner();
        void Menu();
        void ReportBanner(std::ostream& stream);

};