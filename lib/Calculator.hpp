#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include "Dialog.hpp"
#include "UpdateExpenseList.hpp"
#include "GenerateDataFile.hpp"
#include "addTransaction.hpp"
#include "GenerateReport.hpp"

class Calculator {

    public:

        Dialog myDialog;
        UpdateExpenseList myExpenseList;
        GenerateDataFile myDataFiles;
        AddTransaction myTransactionAddition;
        GenerateReport myReport;

        void Prompt();

};

#endif