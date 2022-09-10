#ifndef GENERATE_DATA_FILE_HPP
#define GENERATE_DATA_FILE_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "Helper.hpp"

class GenerateDataFile : public Helper {

    public:

        std::string lines [3];
        std::string dataFilename;

        GenerateDataFile();
        void Generate();
        void Prompt();
        //void GetExpenses();
        
};

#endif