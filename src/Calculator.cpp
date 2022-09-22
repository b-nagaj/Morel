#include <iostream>

#include "../lib/Calculator.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"
#include "../lib/GenerateDataFile.hpp"

void Calculator::Prompt() {

    myDialog.WelcomeBanner();
    
    while (myDialog.option != 4) {
        myDialog.Menu();

        switch (myDialog.option) {
        case 1 :
            myExpenseList.Update();
            break;

        case 2 : 
            myDataFiles.Generate();
            break;

        case 3 :
            myReport.Generate();
            break;
    
        case 4 :
            std::cout << "\nQuitting!\n\n";
        }
    }

    myDialog.option = 0;

}