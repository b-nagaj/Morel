#ifndef REPORT_GENERATOR_HPP
#define REPORT_GENERATOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "../utils/Helper.hpp"
#include "../utils/Dialog.hpp"

class ReportGenerator : public Helper {

    public: 

        Dialog reportGeneratorDialog;
    
    public:

        ReportGenerator();
        void Generate();
        void Calculate();
        double CalculateExpense();
        void Report();
        double GetTotal();

};

#endif