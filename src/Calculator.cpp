#include <iostream>

#include "../lib/Calculator.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"
#include "../lib/GenerateDataFile.hpp"

void Calculator::Prompt() {

    myDialog.WelcomeBanner();
    
    while (myDialog.option != 7) {
        myDialog.Menu();

        switch (myDialog.option) {
        case 1 :
            myReport.Generate();
            break;

        case 2 : 
            std::cout << "\nView A Report";
            break;

        case 3 :
            myDataFiles.Generate();
            break;
        
        case 4 :
            std::cout << "\nUpdate A Report";
            break;
        
        case 5 :
            std::cout << "\nUpdate An Expense";
            break;
        
        case 6 :
            std::cout << "\nHelp";
            break;
        
        case 7 :
            std::cout << "\nQuitting!\n\n";
            exit(0);
        }

        myDialog.option = 0;
    }

}