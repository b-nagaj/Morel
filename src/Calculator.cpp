#include <iostream>

#include "../lib/Calculator.hpp"
#include "../lib/Dialog.hpp"
#include "../lib/ReportGenerator.hpp"
#include "../lib/DataFileGenerator.hpp"

Calculator::Calculator() {

    myDialog.option = 0;
    Prompt();

}

void Calculator::Prompt() {

    myDialog.WelcomeBanner();
    
    while (myDialog.option != myDialog.NUM_MENU_OPTIONS) {
        myDialog.Menu();

        switch (myDialog.option) {
        case 1 :
            myExpenseListUpdater.Update();
            break;

        case 2 : 
            myDataFileGenerator.Generate();
            break;

        case 3 :
            myTransactionAdder.Add();
            break;
        
        case 4 :
            myTransactionDeleter.Delete();
            break;

        case 5 :
            myReportGenerator.Generate();
            break;
    
        case 6 :
            std::cout << "\nQuitting!\n\n";
        }
    }

    myDialog.option = 0;

}