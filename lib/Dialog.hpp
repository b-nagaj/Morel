#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

#include "../lib/Calculator.hpp"

#pragma once

class Dialog {

    public:

        std::string option;
        Calculator myCalculator;

        Dialog();
        void Banner(std::ostream& stream);
        int Menu();

};