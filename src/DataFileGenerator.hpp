#ifndef DATA_FILE_GENERATOR_HPP
#define DATA_FILE_GENERATOR_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <ostream>

#include "Helper.hpp"

class DataFileGenerator : public Helper {

    public:

        std::string lines [3];

        DataFileGenerator();
        void Generate();
        void Write();
        
};

#endif