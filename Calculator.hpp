#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#pragma once

class Calculator {

    public:

        std::string month;
        std::string choice;
        int option;

        void Prompt();
        void GenerateAReport();

};