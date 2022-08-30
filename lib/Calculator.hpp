#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"
#include "../lib/GenerateDataFile.hpp"

#pragma once

class Calculator {

    public:

        Dialog myDialog;
        GenerateReport myReport;
        GenerateDataFile myDataFiles;

        void Prompt();
        void GenerateReports();

};