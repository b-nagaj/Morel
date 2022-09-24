#include <iostream>

#include "../lib/Calculator.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/GenerateReport.hpp"
#include "../lib/GenerateDataFile.hpp"

void Calculator::Prompt() {

    myDialog.WelcomeBanner();
    
    while (myDialog.option != myDialog.NUM_MENU_OPTIONS) {
        myDialog.Menu();

        switch (myDialog.option) {
        case 1 :
            myExpenseList.Update();
            break;

        case 2 : 
            myDataFiles.Generate();
            break;

        case 3 :
            myTransactionAddition.Add();
            break;

        case 4 :
            myReport.Generate();
            break;
    
        case 5 :
            std::cout << "\nQuitting!\n\n";
        }
    }

    myDialog.option = 0;

}