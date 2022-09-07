#include "../lib/Dialog.hpp"
#include "../lib/UpdateExpenseList.hpp"
#include "../lib/GenerateDataFile.hpp"
#include "../lib/GenerateReport.hpp"

#pragma once

class Calculator {

    public:

        Dialog myDialog;
        UpdateExpenseList myExpenseList;
        GenerateReport myReport;
        GenerateDataFile myDataFiles;

        void Prompt();

};