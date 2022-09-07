#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"

#pragma once

class GenerateDataFile {

    public:

        Dialog generateDataFileDialog;
        GenerateReport generateDataFileReport;
        std::string month;
        std::string path;
        std::string dataFilename;
        std::ifstream inputFile;
        std::ofstream outfile;

        GenerateDataFile();
        void Generate();
        void Prompt();
        void Read();
        bool ValidatePath();
        bool ValidateMonth();
        
};