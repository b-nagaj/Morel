#include <iostream> 
#include <string>
#include <fstream>
#include <ostream>

//#include "Calculator.hpp"

class Dialog {

    public:

        std::string option;
        Calculator myCalculator;

        Dialog();
        int Menu();

};