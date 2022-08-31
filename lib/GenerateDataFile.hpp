#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#pragma once

class GenerateDataFile {

    public:

        std::string month;
        std::string path;
        std::string dataFilename;
        std::string dataFilenamePath;
        std::ofstream outfile;

        GenerateDataFile();
        void Generate();
        void Prompt();
        
};