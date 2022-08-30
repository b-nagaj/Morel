#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ostream>
#include <algorithm>
#include <vector>

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
            GenerateReports();
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

void Calculator::GenerateReports() {

    //Dialog GenerateReportDialog;
    //GenerateReport myReport;

    std::cout << "\nGenerate A Report";
    std::cout << "\n\nMonth: ";
    std::string month;
    std::cin >> month;

    bool validMonth = false;
    for (int i = 0; i < 24; i++) {
        if (myReport.validMonths[i] == month) {
            validMonth = true;
            break;
        }
    }

    if (validMonth) {
        std::cout << "\nMake an expense report for " << month << "?" << "(Y/N) ";
        std::string yesNo;
        std:: cin >> yesNo;

        if (yesNo == "Y" || yesNo == "Yes" || yesNo == "y" || yesNo == "yes"){
            myReport.SetMonth(month);
            myReport.Calculate();
        }
        else {
            myDialog.Menu();
        }
    }
    else {
        myDialog.errorMessage = "\nERROR: The value you entered is not a real month";
        std::cout << myDialog.errorMessage;
    }

    myDialog.option = 0;

}