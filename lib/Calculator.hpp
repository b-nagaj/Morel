#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "Dialog.hpp"
#include "UpdateExpenseList.hpp"
#include "GenerateDataFile.hpp"
#include "GenerateReport.hpp"

class Calculator {

    public:

        Dialog myDialog;
        UpdateExpenseList myExpenseList;
        GenerateReport myReport;
        GenerateDataFile myDataFiles;

        void Prompt();

};

#endif