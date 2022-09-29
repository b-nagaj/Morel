#ifndef REPORT_GENERATOR_HPP
#define REPORT_GENERATOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "Helper.hpp"
#include "Dialog.hpp"

class ReportGenerator : public Helper {

    public: 

        Dialog reportGeneratorDialog;
    
    public:

        ReportGenerator();
        void Generate();
        void GetMonth();
        void Calculate();
        double CalculateExpense();
        void Report();
        void DisplayExpenses();
        double GetTotal();

};

#endif