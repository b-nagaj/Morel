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

void Calculator::Prompt() {

    Dialog myDialog;
    myDialog.WelcomeBanner();
    
    while (myDialog.option != 6) {
        myDialog.Menu();

        switch (myDialog.option) {
        case 1 :
            GenerateAReport();
            break;

        case 2 : 
            std::cout << "\nView A Report";
            break;
        
        case 3 :
            std::cout << "\nUpdate A Report";
            break;
        
        case 4 :
            std::cout << "\nUpdate An Expense";
            break;
        
        case 5 :
            std::cout << "\nHelp";
            break;
        
        case 6 :
            std::cout << "\nQuitting!\n\n";
            break;
        }
    }

}

void Calculator::GenerateAReport() {

    Dialog GenerateReportDialog;
    GenerateReport myReport;

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
            GenerateReportDialog.Menu();
        }
    }
    else {
        GenerateReportDialog.errorMessage = "\nERROR: The value you entered is not a real month";
        std::cout << GenerateReportDialog.errorMessage;
    }

}